# Unreal Engine 5 JSON Target Shooting Test

This project is a small FPS prototype created for a technical test using Unreal Engine 5.7 and C++.

## Project Overview

The goal of this project was to build a first-person shooting prototype that reads target data from an online JSON file and uses that data to spawn interactive boxes in the level.

Each spawned box uses JSON-driven values for:
- type
- color
- health
- score
- transform data

The player can shoot the boxes using a line trace shooting system. When a box is destroyed, the player earns points and the score updates on the UI.

## Features

- Fetches JSON data from an online source using Unreal's HTTP module
- Parses target type data and object spawn data from JSON
- Dynamically spawns boxes based on parsed JSON entries
- Applies box color at runtime using a material parameter
- Assigns different health and score values based on box type
- Uses line trace shooting for hit detection
- Reduces box health when shot
- Destroys boxes when health reaches zero
- Updates the player score through a UMG widget

## Technical Details

### JSON Fetching
The project sends an HTTP GET request to the provided online JSON source using Unreal Engine's native HTTP module.

### JSON Parsing
The returned JSON is parsed using Unreal's `Json` and `JsonUtilities` modules.

The JSON contains:
- `types`: definitions for each box type
- `objects`: instances to spawn in the level

Each type includes:
- name
- color
- health
- score

Each object includes:
- type
- transform
  - location
  - rotation
  - scale

### Box Spawning
After the JSON is parsed:
- the object list is read
- the correct box actor is spawned for each entry
- transform values are applied
- type-based health, score, and color are assigned

### Material / Color Logic
Each box uses a material that supports a dynamic color parameter.
At runtime, the color value from the JSON data is applied through C++ using a dynamic material instance.

### Shooting / Damage Logic
The player shoots using a line trace.
When a line trace hits a box:
- the box takes 1 damage
- its health is reduced
- if health reaches zero, the box is destroyed
- the player is awarded the box's score value

### UI
A UMG widget is used to display the player's current score.
The widget updates whenever a box is destroyed.

## Folder Structure

The source code is organized using Public and Private folders, with feature-based separation.

- `Source/InternshipTest/Public`
- `Source/InternshipTest/Private`
- `Source/InternshipTest/Variant_Horror`
- `Source/InternshipTest/Variant_Shooter`

This structure was kept to match the broader module layout while maintaining clearer separation between headers and source files.

## Tech Used

- Unreal Engine 5.7
- C++
- HTTP Module
- Json / JsonUtilities
- UMG

## Challenges Faced

- Parsing nested JSON data correctly
- Matching object entries with their type definitions
- Converting JSON color data into runtime material values
- Applying transform data correctly when spawning actors
- Updating score UI from gameplay events
- Reorganizing code into a cleaner Public / Private structure without breaking includes

## How I Solved Them

- Used Unreal's native HTTP and JSON systems to download and parse the data
- Read type definitions first, then used them to configure spawned objects
- Applied box colors through dynamic material instances in C++
- Used parsed transform data to set location, rotation, and scale during spawn
- Connected box destruction logic to score update logic in the UI flow
- Updated include paths and folder structure so the project still compiled correctly after reorganization

## Build / Run Steps

1. Open the `.uproject` file in Unreal Engine 5.7
2. Generate Visual Studio project files if prompted
3. Build the solution
4. Open the main level for the shooting prototype
5. Press Play in the editor

## How to Test

1. Launch the project
2. Start Play mode
3. Confirm that boxes are spawned from the JSON data
4. Shoot different boxes
5. Verify that:
   - different boxes have different colors
   - different boxes have different health values
   - score increases when a box is destroyed
   - the score UI updates correctly

## Assumptions / Limitations

- This project is a technical test prototype, not a full game
- The shooting system uses a simple line trace implementation
- The focus of the project is JSON-driven spawning and gameplay logic
- Error handling can be expanded further for additional edge cases

## Video Demo

https://youtu.be/dc7tKCqkcoU
