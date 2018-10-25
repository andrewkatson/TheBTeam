[Unreleased]




[0.0.2] - 2018 - 10 - 24
### Added
- SoundManager class skeleton [@jeremyelkayam][https://github.com/jeremyelkayam]
- Player class implementation with docs
- ActorInterface ~~skeleton~~ implementation with docs
- SoundManager implementation with docs
  - NO CONSTRUCTOR YET BUT THERE IS A PSEUDOCODE VERSION FOR WHEN WE HAVE SOUNDS
- WaveManager skeleton with shitty documentation
- ProjectileManager skeleton
- Projectile skeleton
- MeleeUnit skeleton
- HitpointBar skeleton
-Event Manager, Event Type, Event Interface, Event Data Interface added with implementation[@meisong1997][https://github.com/meisong1997]
-TowerManager skeleton[@andrewkatson][https://github.com/andrewkatson]
-TowerInterface
-MeleeTower skeleton
-RangedTower sekeleton
-UserInputManager skeleton
-UserKeyPressEvent skeleton
-UserKeyPressEventData skeleton
-RandomVariates class holds all the random variate generation functions now

### Changed
- MapFactory places obstacles first and uses invisible obstacles that block the path
  but not towers [@andrewkatson][https://github.com/andrewkatson]
- BoardManager stores map made from mapgenerator and provides access to them
- BoardManager can generate new maps
- BoardManager, TowerManager, GameState, ProjectileManager, SoundManager, WaveManager
  Player, GameLogic, UserView, CompView all have delegateMethod functions and a reference
  passed to them for the event manager so they can register and deregister events
  as well as push new ones to the event queue
- MapFactory now deals with getting stuck by removing an obstacle
- CompView psuedocode [@KP-HB][https://github.com/KP-HB]
- UserView psuedocode

### Removed
- Unused methods from MapFactory [@andrewkatson][https://github.com/andrewkatson]

[0.0.1] - 2018 - 10 - 18
### Added
- Fonts folder with sample Fonts [@andrewkatson][https://github.com/andrewkatson]
- Textures folder
- Game class
- GameLogic class skeleton
- UserView class skeleton
- CompView class skeleton
- MapFactory class that constructs a map for each game
- Direction class that keeps track of a direction
- MapChoices container class to hold all map generation customization values
- rngs file for random number generation (from a class library)
- BoardManager class handles the map factory and the layouts
- GameState class with enum to store state [@jeremyelkayam][https://github.com/jeremyelkayam]
- Documentation for GameState and GameLogic
