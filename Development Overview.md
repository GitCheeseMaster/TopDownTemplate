# Development Overview

In this documentation, I will go over the details of the features, C++ files, actors, blueprints, and other files I added to the project.

## Major Features

* Added a jet pack that allows the player to fly around.
* Added a simple HUD to show the remaining fuel of the jet pack.
* Changed the player controls from point-and-click to WASD and mouse to look.
* Added strafing blends/animations to the player, using free assets provided by the Unreal Marketplace.
* Added a jump action.
* Modified the jump action so it can activate the jet pack.
* Added a short obstacle course to test out the jet pack.
* Added an actor that loads levels upon collision.

## Hours Spent

In total, I spent around 38 hours on this project. Of those 38, around 24 were spent on development, and the remaining 14 hours were spent on:
* Setting up the environment properly.
* Watching YouTube tutorials.
* Reading the official Unreal documentation.

## C++ Files

### JetPackActor

The class for the Jet Pack Actor. This class primarily holds the jet pack component. I would eventually have this actor interface better with its owner via an EquipmentUser/EquipmentProvider component combo.

For prototyping, it is acceptable for actors to have assumptions about their children, components, etc. However, for production, there should be proper interfacing classes to reduce dependencies and better encapsulate code.

### JetPackComponent

The star of the show, the jet pack component. It offers an API for the PlayerController to activate/deactivate the jet pack, calculates the desired impulse to be applied to the player, and manages the fire effects when the jet pack is active.

I wanted the class to offer an impulse that could be used by its user so that the component could be attached to any kind of actor.

I don't like how the component assumes that all the Niagara components are effects that should be on while the jet pack is active. I was not sure of the best way to handle calling effects in Unreal. I am used to having some kind of effect interface component and using it to request an effect by a string/hash.

### LoadLevelArea

This class loads the desired level when the player overlaps with its collision. It is very straightforward and useful for prototyping.

However, I would not use this actor for actual production. There would need to be some kind of level loading sequence or manager, and all requests would go through it. (This kind of actor would be good for streaming parts of a bigger level, however.)

### MathUtility

A math utility that holds only one function. I needed a LERP function that could handle angles properly. I didn't see anything in FMath, but maybe Unreal offers something else?

Since this is just a math utility, I initially tried to add a header file to the solution manually, but Unreal didn't accept that. I guess the hot reload system needs metadata about each file, so I made it a UObject. I am not sure this is the best way to handle utility files, but it worked.

### TopDownCharacter

This is the original TopDownCharacter class, modified to handle the jet pack functionality. It searches through attached actors for a jet pack component (it assumes there will only be one!) and caches it.

It also creates the HUD, adds it to the viewport, and updates the FuelBar from the cached jet pack component.

As stated above, for prototyping, it is acceptable to cache a component from an attached actor. For production, the Character would interface through its equipment component and make requests for the jet pack via it.

I don't like how I am currently applying the jet pack impulse to the player's movement component. It seems hacky to change the movement mode externally and could lead to problems in the future. I think the movement component should be modified to use the jet pack's impulse internally and properly handle the changing of movement modes.

### TopDownGameMode

I didn't touch this file. (I was thinking of adding a timer to the obstacle course level.)

### TopDownPlayerController

This is the original TopDownPlayerController that I modified. As stated above, I changed the controls from point-and-click to WASD movement and mouse to look. The WASD keys and the mouse inputs both change the 2D vectors, so gamepad controls could easily be added.

I added an action to jump/activate the jet pack. The controller directly accesses the jet pack component through the player, but it would be nice to have some interfacing between these two objects.

### TopDownPlayerHUD

This is a simple widget class to display the fuel gauge.

## Blueprints

### ABP_Manny / BS_MM_Locomotion

I created a blend space and added strafing animations, and modified Manny's animation blueprint to use it.

A lot of the free samples are for shooters, with most animations accounting for holding a gun. I didn't want that for my game, so I looked around for resources with a more neutral stance. The "Game Animation Sample" pack has some nice animations, but they use Unreal's Motion Mapping, which I didn't want to spend a lot of time learning this time around.

So I searched through all the animations the sample provided and cut up some frames from animations that seemed usable. This is why the animations don't loop properly for strafing. But it is good enough for prototyping, in my opinion.

### NS_JetPackEffect

The Niagara system blueprint for the jet pack activation effect. I wanted to make something that looked like fire and smoke. Adding this effect is what really sells the jet pack. Otherwise, you just have a character flying around, and it looks like a debug feature.

### BP_JetPack

The blueprint for the jet pack actor. I made the "model" using the static mesh creation tool. Then I combined all of those into the actor. I wanted to combine all of these into a single mesh, as it is wasteful to have so many actors for such a simple model.

As with the effect, I felt that having a visual representation of the jet pack was important to sell the idea.

### BP_TopDownPlayerHUD

The blueprint for the HUD. I fashioned a progress bar into the fuel gauge and linked it with the C++ class I explained above.

### BP_FloatingText

A simple blueprint that holds a text render component. I used it to label my load area doors placed in the levels.

### BP_LoadLevelArea

The blueprint for the C++ class I explained above. The blueprint just exists so the actor is placeable.

### BP_MovingPlatform

A simple moving platform blueprint used in the obstacle course level.

### BP_TopDownCharacter

The blueprint for the C++ class I explained above. I directly added the BP_JetPack as an attached actor to this BP.

I was going to spawn the jet pack actor from code, but the editor makes it much easier to adjust the position just right.

## Conclusion

Though this was my first time really diving into Unreal Engine, I had a blast (pun intended). I thought the UE coding conventions were a little strange, using CamelCase for everything and not using 'm' for class member, as in `float mFuelAmount;`. However, I think I would quickly acclimate if I were to see it every day.

For prototyping, Unreal Engine seems amazing, but when things shift to production, I wonder how many of the useful features will have to be tossed out for the sake of performance. I am interested to see how an actual UE game is made.

## Free Materials

The free materials I added to the project:

### Game Animation Sample
[https://dev.epicgames.com/documentation/en-us/unreal-engine/game-animation-sample-project-in-unreal-engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/game-animation-sample-project-in-unreal-engine)
