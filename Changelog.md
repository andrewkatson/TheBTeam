[Unreleased]

###Added
- Textures added for other units as well as all tower upgrades, as follows: [@jeremyelkayam][https://github.com/jeremyelkayam]
 - Kids
  - Fat Kid
  - Skinny Kid
 - Pizza Towers
  - Pepperoni
  - Deep Dish
  - Meat Lovers'
 - Drink Towers
  - Energy Drink
  - Slushie
  - Gravy Boat
 - Candy Towers
  - Regular M&M
  - Peanut M&M
  - Peanut Butter M&M
 - Fry Towers & Units
  - Waffle Fry
  - Crinkle Cut Fry
  - Spicy Fry
- yes, I did all this... it took many hours

###Changed
- Improved unit animations [@jeremyelkayam][https://github.com/jeremyelkayam]
- OptionsMenuScreen now sends events to player, boardmanager, and wavemanager [kp-hb][https://github.com/kp-hb]
- Player has a handleoptionselectedevent method
- boardmanager has a handleoptionselectedevent method
- wavemanager has a handleoptionselectedevent method


###Fixed
- Units now face the direction in which they're moving (when set using setDirection) [@jeremyelkayam][https://github.com/jeremyelkayam]


[0.7.0] 2018-12-02

###Added
- attack rate for all units [@andrewkatson][https://github.com/andrewkatson]
- upgrade system for aspects of the melee and range towers for more customizaton
- collision manager skeleton added
- ENEMY UNIT MOVEMENT. [@jeremyelkayam][https://github.com/jeremyelkayam]
- __WORKING__ ENEMY UNIT MOVEMENT.
- Units despawn and knock off player health when they reach the exit tile

###Changed  
- melee towers spawn units surrounding their flag in the right spaces [@andrewkatson][https://github.com/andrewkatson]
- mouseover to see what each upgrade button is
- upgrade circle now adjusts to never be off the screen
- MeleeUnit::move() now takes an angle in radians to move. [@jeremyelkayam][https://github.com/jeremyelkayam]
- Units no longer travel at the edges of a path; they travel roughly toward the center (perturbed randomly) of each path.
- Multiplier on unit health for decreasing of player health moved to constants.xml
 - Greatly decreased this multiplier
- Animation speed is now dependent on unit movement speed

###Fixed
- seg faults from trying to destroy unitialized box2d bodies [@andrewkatson][https://github.com/andrewkatson]
- allied units now move to the rally point correctly
- seg fault when units are spawned
- Enemies no longer stop right before moving to the exit[@jeremyelkayam][https://github.com/jeremyelkayam]
- MeleeUnit::move() behaves like it's supposed to instead of doing weird and erratic garbage
- A bug where enemy units would only spawn from one entrance in the board

###Bugs
- Sometimes enemies stray off the path

[0.6.0] 2018-12-01
###Added
- DifficultyChangeEvent,DifficultyChangeEventData [@jeremyelkayam][https://github.com/jeremyelkayam]
- Pressing w now creates a new wave and begins spawning its units if a wave is not in progress
- Enemy units now spawn at a random position at the edge of their entrance square
- Many assertions in WaveManager so that functions are activated from safe contexts

###Changed
- Many major changes to wave generation [@jeremyelkayam][https://github.com/jeremyelkayam]
 - Wave generation tweaked for debugging and to accomodate better randomization
 - Inclusion of difficulty as an instance variable
  - updated when adjusted by the player
 - More Events!
  - Takes ActorDestroyedEvents and removes units accordingly
  - Takes MapGeneratedEvents and updates map info accordingly
  - Takes LevelChangeEvents and sets up a new wave set for each new level
  - Takes DifficultyChangeEvents and updates difficulty setting accordingly
  - Takes and raises WaveChangeEvents every time a wave is signaled to begin or end.
 - WaveManager spawns units in its update function once every 10th of a second (adjustable)
 - CompView only moves enemy units if there are units to move

###Fixed
- Sometimes units were initialized with bogus coordinates [@jeremyelkayam][https://github.com/jeremyelkayam]
- CompView will now only direct units to move to path tiles (previously they could move onto other tiles)

###Bug
- seg faults every time the game creates an actor or tower

###Removed
- MeleeUnit::getID() (removed for being redundant and confusing) [@jeremyelkayam][https://github.com/jeremyelkayam]
- WaveManager no longer selects its unit types from an array; it now allocates them in hardcoded fashion
 - The instance variable `enemies` and function `setupPossibleEnemies` are no longer necessary, so they no longer exist.

[0.5.0] 2018-11-29
###Added
- ActorCreatedEvent,ActorCreatedEventData [@andrewkatson][https://github.com/andrewkatson]
- AllyCompView to deal with tower attacking, allied unit attacking and projectile hits

###Changed
- playing screen draws enemies to the screen [@andrewkatson][https://github.com/andrewkatson]
- all range towers now have the capacity to create projectiles of their type when asked to attack
- units scale properly so they do not appear as large as towers
- projectiles have a vector of attack based on the coordinates of the unit they target
- clicking on a tower will show its attack/spawn radius in light blue
- all projectiles face same way as eachother
- projectiles will go towards the point they are fired at and then when they reach it they will trigger
  a projectile explosion (handled by gamelogic) and then a actor destroyed event is made
- game has a proper delta function for speeds
- CompView controls enemy melee units and sets their direction to move toward the map exit
- all towers use floats for their coordinates
- radius circles are now centered
- all melee units will be initalized to the center of the tower that spawns them
- all non dead allied melee units will be drawn
- AI for enemy units [@jeremyelkayam][https://github.com/jeremyelkayam]
 - Check for whether the space is actually a path tile
- When a unit leaves the map (by reaching the exit) appropriate events are triggered and delegated.
- MapGeneratedEvent now includes information on the new map which is used by WaveManager

 ###Removed
 - all scaling from the header! [@andrewkatson][https://github.com/andrewkatson]

 ###Fixed
 - sometimes objects were not being removed [@andrewkatson][https://github.com/andrewkatson]

 ###Bug
 - sometmes when towers and/or obstacles are removed the change is overwritten in the boardmanager [@andrewkatson][https://github.com/andrewkatson]

[0.4.0] 2018-11-15
###Added
- MapGeneratedEvent and MapGeneratedEventData [@andrewkatson][https://github.com/andrewkatson]
- TextureLoader
- Textures for cafeteriatable and trashcan
- Blank textures for all the type of tower until they are finished
- PlayingScreenHeader to draw the information about the current play ontop of the
  playingScreen
- LevelChangeEvent, LevelChangeEventData, BalanceChangeEvent, BalanceChangeEventData
- SellTower Button for the playing screen  
- BuyTowerOption class to encapsulate the option draw to the screen on the buy tower screen
- Textures for AverageKidUnit [@jeremyelkayam][https://github.com/jeremyelkayam]
- Textures for NormalFryUnit
- Textures for CheesePizza tower
- Texture for Soda tower
- Textures for Mini M&M tower
- Textures for NormalFry tower
- Textures for projectiles of all above towers
- XML tags for the OptionsMenu Switchers [kp-hb][https://github.com/kp-hb]


###Changed
- color constants for tiles on the floor of a map (path, school, and exit) [@andrewkatson][https://github.com/andrewkatson]
- access to the map customization options through gameLogic
- access to the tile sizes through gamelogic
- all redundant include strings
- all resources loaded in constructors moved to init methods
- all tiles have their colors shifted by small amounts (to make it look more diverse
- all projectiles, towers, units, and obstacles load their respective textures from
  the textures file
- Towers and Obstacles no longer are passed their own type id
- Towers, Obstacles, Projectiles, and Units all load their own type ids in their constructors
- TextLoader now treats any typeID as distinct from a normal string
- Towers draw to screen when placed
- Userview call for options Screen from 7 to 6 [kp-hb][https://github.com/kp-hb]
- OptionsMenuScreen screen has 6 options, dimensions changed
- Switcher has textloader
- actors have an id that is the same as their address
- Header displays wave, level, balance, and hitpoints. will update with events changing any of those (can be hidden)
- Player now creates events when the level, balance, hitpoints, or wave are changed
- Map Factory uses a slight randomness to generate the board size using the cafeteria choice
- Enemy waves are now stored in a map with key uniqueID
- Buy Tower Screen now draws the options available to the screen
- Buy Tower Screen displays all tower possibilities
 [@jeremyelkayam][https://github.com/jeremyelkayam]
- MeleeUnits switch their walking sprite every half-second to "animate" crudely

[0.1.5] 2018-11-7
###Added
- TowerRemoveEvent, TowerRemveEventData [@andrewkatson][https://github.com/andrewkatson]
- OptionSelectedEvent, OptionSelectedEventData, LoseHitpointsEvent, LoseHitpointsEventData, WaveChangeEvent, WaveChangeEventData [@meisong1997][https://github.com/meisong1997]
- Storage of entry positions and distance vector within WaveManager [@jeremyelkayam][https://github.com/jeremyelkayam]
- Function to reformat distance vector to get distances for each entrance position
- Normalization of distances based on furthest distance in vector
- Sorted map storing distances and entrances in WaveManager
- Set/getters for world and board coordinates of ActorInterfaces (xcor,ycor,row,col)

###Changed
- GameLogic now updates the balance of the player appropriately whether
 you buy a tower, remove an obstacle, or remove a tower [@andrewkatson][https://github.com/andrewkatson]
- MapFactory allows for paths to take whatever is their shortest path to exit
  if the path crosses an exit path at any point then we do not draw over it
- BoardManager walks through all paths and assigns them new distances
  so that each distance on the path reflects the number of tiles between that tile and the exit
- All Projectiles, Units, and Towers have access to eventManager and textLoader
- Melee Towers now handle respawning units and actor destroyed events
- All Units and projectiles have access to getters and setters for their position (in euclidean coordinates and in row-col)
- Buttons can now be set to visible or non visible (visible by default)
- UserView registers and then deregisters the delegates of whatever screen it is switching to
- Buy Tower screen can be navigated to from Playing Screen (and it can return as well)
- optionsMenuScreen moveRight, Switcher.hpp len and public functions [@KP-HB][https://github.com/KP-HB]
- Changed OptionSelected event data type from string to integer [@meisong1997][https://github.com/meisong1997]
- makeWave now sets enemy coordinates at one of the map's entrances [@jeremyelkayam][https://github.com/jeremyelkayam]
 - This choice is random but biased toward far entrances when a level begins
 - As a level progresses and more waves arrive, the choice becomes more biased toward closer entrances
 - This took a lot of work to figure out how to do




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
- Now menu screen works and switches between the options [@KP-HB][https://github.com/KP-HB]
- Number of waves is generated with a normal distribution based on difficulty and level[@jeremyelkayam][https://github.com/jeremyelkayam]
- Wave members have a random adjustment to their stats (adjustment increases as difficulty progresses)
- Units are now determined by a wave weight (generated with a normal distribution) and weighted values for each unit
- WaveManager constants moved to XML file


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
