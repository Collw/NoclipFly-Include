# NoclipFly Integration Guide

This README provides a step-by-step guide on how to integrate the `NoclipFly` system into your SA:MP gamemode. Follow the instructions carefully to ensure the system works smoothly in your project.

## 1. **Requirements**
- **SA:MP Server Package** (Ensure you have the latest SA:MP server version).
- **Pawno Compiler** (Included in the SA:MP package).
- **ZCMD** Command Processor (used for handling commands efficiently).
- **MapAndreas Plugin** (to assist with positioning, though this is optional).

## 2. **Files Needed**
- `noclipfly.inc`: The include file with all the necessary functions for activating the fly mode (noclip).
- Your gamemode `.pwn` file where the noclip system will be integrated.

## 3. **Installation Steps**

### Step 1: Add the `noclipfly.inc`
1. Place the `noclipfly.inc` in the **`/pawno/include/`** directory of your SA:MP server.
2. Ensure that the include is properly referenced in your gamemode file (`.pwn`).

### Step 2: Modifying Your Gamemode
1. Open your gamemode `.pwn` file in Pawno.
2. At the top of your gamemode, include the necessary libraries by adding the following lines:

    ```pawn
    #include <a_samp>
    #include <noclipfly>
    #include <zcmd>
    ```

3. In the `OnGameModeInit()` callback, initialize the Noclip system:

    ```pawn
    public OnGameModeInit()
    {
        SetGameModeText("Your Gamemode Name");
        AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
        
        NoclipInit(); // Initialize noclip mode for all players

        return 1;
    }
    ```

4. In the `OnPlayerConnect()` callback, initialize Noclip data for each player:

    ```pawn
    public OnPlayerConnect(playerid)
    {
        NoclipConnect(playerid); // Initialize noclip data when a player connects
        return 1;
    }
    ```

5. In the `OnPlayerUpdate()` callback, update the player's noclip status:

    ```pawn
    public OnPlayerUpdate(playerid)
    {
        NoclipUpdate(playerid); // Update player's movement if they are in fly mode
        return 1;
    }
    ```

6. Add the `fly` command to toggle the noclip fly mode on or off:

    ```pawn
    CMD:fly(playerid)
    {
        if(GetPVarType(playerid, "FlyMode")) 
            CancelFlyMode(playerid); // Turn off fly mode
        else 
            FlyMode(playerid); // Turn on fly mode
        
        return 1;
    }
    ```

### Step 3: Compilation
1. Save the `.pwn` file.
2. Open Pawno and compile your gamemode. Ensure there are no errors.
3. Place the compiled `.amx` file in the **`/gamemodes/`** directory.

### Step 4: Configuration
1. Open the **`server.cfg`** file in the root of your SA:MP server.
2. Set your gamemode to the one you just compiled. For example:

    ```
    gamemode0 yourgamemode 1
    ```

3. Save the `server.cfg` file.

### Step 5: Testing
1. Start your SA:MP server.
2. Connect to your server and type `/fly` to activate the fly mode.

## 4. **Commands Available**
- **/fly**: Toggles the fly mode (noclip) for the player.

## 5. **Notes**
- The system automatically resets noclip status when the player connects or the server initializes.
- The fly mode allows the player to move freely in the air using camera control and keyboard inputs.
