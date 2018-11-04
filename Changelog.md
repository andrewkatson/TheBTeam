[Unreleased]

###Added
- TowerRemoveEvent, TowerRemveEventData [@andrewkatson][https://github.com/andrewkatson]

###Changed
- GameLogic now updates the balance of the player appropriately whether
 you buy a tower, remove an obstacle, or remove a tower [@andrewkatson][https://github.com/andrewkatson]


[0.1.2]
##Added
- StateChangeEvent, StateChangeEventData[@andrewkatson][https://github.com/andrewkatson]
- NotATower to indicate to stand for an empty space
- ActorDestroyedEvent, ActorDestroyedEventData, ActorAttackEvent, ActorAttackEventData [@meisong1997][https://github.com/meisong1997]
- Floating-point [double] loading in TextLoader [@jeremyelkayam][https://github.com/jeremyelkayam]

###Changed
- MapFactory now uses an A* BFS to find paths through the
  map [@andrewkatson][https://github.com/andrewkatson]
- Playing Screen now writes the maps to console for testing
- Tower Manager now keeps track of every kind of tower and obstacle
  separate from their list of upgrdes (uses same objects as the upgrade map)
- TowerManager adds obstacle objects to the towersPlaced as soon
  as they are made when a new map is generated (facilitated by GameLogic)
- GameLogic has the capacity to check if a particular tower can be purchased
- GameLogic can return a vector of the upgrades for a tower given its tile
- GameLogic can make a tower creation event (to be handled by board manager and tower manager)
- GameLogic can be queried for an attempted purchase of a particular tower type
- BoardManager sets up all obstacles made at the start of the game
- Now menu screen works and switches between the options
 [@KP-HB][https://github.com/KP-HB]
 - Fully fleshed out generation of wave members [@jeremyelkayam][https://github.com/jeremyelkayam]

###Fixed
- memory issue caused by improperly initialized shared pointers [@andrewkatson][https://github.com/andrewkatson]
- Improper random-number-generation in WaveManager::makeWave [@jeremyelkayam][https://github.com/jeremyelkayam]



[0.1.0]

###Added
- MousePressEvent, MousePressEventData to regsiter mouse presses [@andrewkatson][https://github.com/andrewkatson]
- MainMenuScreen, PlayingScreen, RestartScreen, OptionsMenuScreen, and RestartScreen
- KeyPress checks for O, S, Enter, UpArrow,DownArrow,LeftArrow, RightArrow

###Changed
- TowerInterface has a radius of attack for each tower[@andrewkatson][https://github.com/andrewkatson]
- RangeTower has a rate of fire
- UserInputManager handles mouse presses (left or right)
- MapFactory will reset a path if it gets stuck (soft reset)
- MapFactory will now reset the whole board and start over if a path cannot be restarted
  successfully (hard reset)
- TowerManager has all tower types in the old map for upgrades and any empty tile can
  be "upgraded" into any of the four basic types
- MainMenuScreen and OptionsMenuScreen now take key presses


###Fixed
- EventType not saving the address passed as its type [@andrewkatson][https://github.com/andrewkatson]
- MapFactory no longer crashes or fails to generate a board
- Random seg fault with event manager. made the raw pointers shared pointers!

###Known Issues
- Segfault occurs randomly after board creation. It is unknown what causes this.

[0.0.3] - 2018 - 10 - 27

#Added
- All tower classes (CheesePizza, CrinkleFry, DeepDish, EnergyDrink, Gravy, MeatLovers,
  MiniM&MS, NormalFry, NormalM&MS, PeanutButterM&Ms, PeanutM&Ms, PepperoniPizza,
  Slushie, Soda, SpicyFry, WaffleFry)[@andrewkatson][https://github.com/andrewkatson]
- Events, Obstacles, and Towers folders
- CafeteriaTable Obstacle, TrashCan Obstacle
- Projectiles Folder
- CheesePizzaProjectile, DeepDishProjectile, EnergyDrinkProjectile, GravyProjectile,
  MeatLoversProjectile, MiniMMSProjectile, NormalMMSProjectile, PeanutButterMMSProjectile,
  PeantuMMSProjectile, PepperoniPizzaProjectile, SlushieProjectile, SodaProjectile
- NormalyFryUnit, SpicyFryUnit, WaffleFryUnit, CrinkleFryUnit
- tinyxml2 library [@jeremyelkayam][https://github.com/jeremyelkayam]
- TextLoader class to load text values from xml
- XML files for storage of constants and strings
- Enemy type classes (FatKidUnit, SkinnyKidUnit, AverageKidUnit)

###Changed
- CMakeLists now compiles recursively so subdirectories will be included in compilation [@andrewkatson][https://github.com/andrewkatson]
- TextLoader held by the Game class and loads in all constants and strings
- All constants and strings replaced with xml
- Executable now loads window title from xml file
- WaveManager initializes the vector of possible enemy units
- TowerManager makes a map of possible upgrades from any towertype
- NormalFry,CrinkleFry,SpicyFry,WaffleFry all create a set of units to spawn
- CheesePizzaProjectile, DeepDishProjectile, EnergyDrinkProjectile, GravyProjectile,
  MeatLoversProjectile, MiniMMSProjectile, NormalMMSProjectile, PeanutButterMMSProjectile,
  PeantuMMSProjectile, PepperoniPizzaProjectile, SlushieProjectile, SodaProjectile
- NormalyFryUnit, SpicyFryUnit, WaffleFryUnit, CrinkleFryUnit have default values
- All RangeTower types now are initialized with their own projectiles
- Projectile class holds an id for every projectile and a vector describing its direction

###Fixed
- MapFactory no longer endlessely loops when it gets stuck. (removes a wall)


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
- Button constructor includes order for positioning (untested)
- Main Menu skeleton (UserView)

###Fixed
- compile-time erros in UserView and CompView classes[@jeremyelkayam][https://github.com/jeremyelkayam]

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
