# Projet : alternative au ChildActorComponent (plugin UE5)

## Objectif
Remplacer UChildActorComponent avec parité fonctionnelle complète (graphes parent et enfant exécutés, réplication, imbrication), en plus robuste, plus constant et plus user friendly.

## Versions cibles
- Unreal Engine 5.5 à 5.8.
- FInstancedPropertyBag et FInstancedStruct sont dans CoreUObject dès la 5.5 : aucune dépendance au plugin StructUtils.
- Toute API qui diffère entre 5.5 et 5.8 passe par ENGINE_MINOR_VERSION.

## Décisions d'architecture
- L'enfant est une projection : il n'est jamais sérialisé dans le niveau. Seul un descripteur vit dans le composant du parent.
- Le descripteur contient la classe (TSoftClassPtr), les overrides (FInstancedPropertyBag, pas de UObject template) et un GUID stable du lien.
- Spawn via SpawnActorDeferred, puis application des overrides, puis FinishSpawning. Les FProperty sont mis en cache par classe.
- Réconciliation au rerun du Construction Script : diff du descripteur, recréation uniquement si la classe change. Gère undo/redo, copier-coller et OnObjectsReplaced.
- Éditeur : l'enfant est une preview transient.

## Ordre d'initialisation
- Politique d'ordre configurable : ChildFirst (spawn dans le BeginPlay du composant, donc avant le ReceiveBeginPlay du parent) ou ParentFirst (spawn différé après le BeginPlay du parent). Garantie en serveur et en standalone.
- Barrière : états OwnerBegunPlay et ChildBegunPlay. OnLinkReady se déclenche une seule fois quand les deux sont vrais, dans le graphe du parent et dans celui de l'enfant. Un abonnement tardif est appelé immédiatement.
- La barrière couvre les cas sans ordre garanti : client répliqué, chargement async, streaming, imbrication.
- Convention utilisateur : BeginPlay pour l'init locale, OnLinkReady pour tout ce qui touche à l'autre.

## Autres briques prévues
- UWorldSubsystem comme registre : suivi des liens, streaming, pooling, résolution par GUID, debug.
- Politiques réseau : ServerReplicated / LocalOnEachMachine / ServerOnly.
- Politique à la destruction du parent : Destroy / Detach / Keep.
- Tick prerequisite automatique entre parent et enfant.
- Mode Flatten pour les enfants purement visuels.
- UX : panneau de détails avec class picker et propriétés exposées en ligne (meta LinkedExpose), getter typé (DeterminesOutputType ou K2Node), Data Validation (cycles, classe manquante), component visualizer.

## État actuel
- FLinkedActorDescriptor (LinkedActorDescriptor.h) et UEnhancedChildActorComponent (USceneComponent) posés : spawn différé + overrides + attachement dans BeginPlay (ChildFirst), destruction dans EndPlay.
- Le module est dans EnhancedChildActorComponentModule.h/.cpp. CoreUObject et Engine sont en dépendances publiques.
- FInstancedPropertyBag n'est pas exposable en Blueprint (erreur UHT) : Overrides est EditAnywhere seulement.

- GUID du lien : généré dans PostInitProperties, jamais sur un template (IsTemplate). Conservé au rerun du Construction Script par FEnhancedChildActorComponentInstanceData (tous modes de création : SCS, UCS, instance). Régénéré au copier-coller et à la duplication éditeur (PostEditImport) et au PostDuplicate Normal. Conservé en PIE et en duplication de World.
- Limites connues du GUID : un acteur spawné au runtime a un GUID différent sur le client et le serveur (à répliquer à l'étape réplication). Un niveau chargé plusieurs fois (level instance) donne des GUID en double : le registre devra combiner GUID et niveau.

## Prochaines étapes (dans l'ordre)
1. ~~Stabilité du GUID du lien~~ (fait, compile, PAS ENCORE TESTÉ en éditeur). Tests à faire avant l'étape 2, le GUID est visible en lecture seule dans les détails :
   - Placer un BP contenant le composant, noter le GUID.
   - Modifier une propriété de l'acteur (rerun du Construction Script) : GUID identique.
   - Ctrl+D : la copie a un GUID différent.
   - Sauvegarder, recharger le niveau : GUID inchangé.
   - Lancer le PIE : même GUID dans le monde PIE.
2. Barrière OnLinkReady et politique d'ordre ChildFirst / ParentFirst, avec chargement async de la classe.
3. Réplication (inclure la réplication du GUID).
4. Plus tard : cache des FProperty par classe, preview éditeur et réconciliation.

## Contexte développeur
Dev UE Blueprint (10 ans) et C++ (2 ans), IDE JetBrains Rider. Progression pas à pas, dans l'ordre logique : une fonction est définie avant d'être appelée.