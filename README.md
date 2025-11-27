# External-Fortnite-ESP

# ⚠️ **Educational / Research Purpose Only**  
> This project is created **only for learning**, reverse engineering practice, and understanding how external overlays work with games like Fortnite.  
> We do **NOT** encourage cheating, modifying online games, or violating EULA/TOS.  
> Anything you do is **your responsibility**.


# Features

- **External ESP (non-injected)**
- **Box ESP**
- **Skeleton ESP**
- **Distance ESP**
- **Line ESP**
- **Camera-based line rendering**
- **ImGui overlay**
- **Offset-based memory reading**
- **Supports latest Fortnite versions (using updated offsets)**
# Preview
<img width="1920" height="1080" alt="Screenshot (5)" src="https://github.com/user-attachments/assets/cb2e6c23-637e-4777-b20f-35bec19fdcb1" />

# How to Build
> 1. Install **Visual Studio 2022**  
> 2. Open the solution `ForniteExtenralCheat.sln`  
> 3. Select:  
>    ```
>    Release | x64
>    ```  
> 4. Press **Build → Build Solution**
> 5. Map `shitty_driver.sys`
> 6. Run the compiled `.exe` **as Administrator**
>
> ✔ It's a normal C++ project — no special configuration needed.

# Updating Offsets (When Fortnite Updates)
- Fortnite updates frequently, which means the offsets in your project may become outdated. Before building your project, make sure you’re using the latest offsets.
> Visit the public offsets repository: [Here](https://github.com/paysonism/Fortnite-Offsets/blob/main/offsets.h)

# Technical Overview
> External memory reading using WinAPI
> Overlay rendering using ImGui + DirectX11
> Bone reading through USkeletalMeshComponent
> Player iteration via actor array
> W2S projected through game camera matrices
> Modular memory + rendering system

# Credits
- [Fortnite-Offsets](https://github.com/paysonism/Fortnite-Offsets)
- [External-ImGui-Overlay](https://github.com/3r4y/imgui-external-overlay)

## 🏷️ Tags
> Fortnite ESP, External ESP, Fortnite Cheat, Memory Reading, Aimbot, Offsets, Pattern Scan, GNames, GWrold, SDK Free, Game Hacking, C++ Cheat

<!--
Keywords:
PUBG Mobile ESP
PUBG External Cheat
PUBG 3D ESP
PUBG Memory Hack
PUBG Offsets 2025
PUBG Update Patterns
Pattern Scan
C++ Game Hack
-->



