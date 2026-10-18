# Learning_OpenGL

Code written while following the [Learn OpenGL](https://learnopengl.com/) tutorial series: a small C++ renderer that loads 3D models and lights them with several light types.

> **Work in progress.** This is a learning project, not a finished engine. The code changes as I move through the tutorials, and it contains experiments, commented-out code and TODOs.

## What it shows so far

- **Window and context** with GLFW and glad (OpenGL 3.3 core profile)
- **Free-fly camera** with keyboard movement and mouse look
- **Model loading** with Assimp, including diffuse and specular textures (loaded with stb_image)
- **Lighting** in a custom GLSL shader, with directional, point and spot lights (the spot light follows the camera, like a torch)
- **Shader and texture helper classes**

## Controls

| Input | Action |
| --- | --- |
| `W` `A` `S` `D` | Move the camera |
| Mouse | Look around |
| `Space` | Toggle the rotation speed value |
| `Esc` | Quit |

## Requirements

- Windows with **Visual Studio 2022** (the project uses the v143 toolset)
- An OpenGL 3.3 capable GPU

The headers for GLFW, Assimp, GLM, glad and stb_image are in `Dependencies/`, but compiled binaries are not (`*.lib` and `*.dll` are git-ignored). You need to supply:

- `glfw3.lib` in `Dependencies/GLFW/lib-vc2022`
- `assimp-vc143-mt.lib` in `Dependencies/assimp/src`
- the Assimp DLL next to the built executable

These paths come from `Learning_OpenGL.vcxproj`, so adjust them there if you keep your libraries elsewhere.

## Building and running

1. Open `Learning_OpenGL.sln` in Visual Studio 2022.
2. Add the library files described above.
3. Choose a configuration and build.
4. Run the project. A post-build step copies the `Resources` folder next to the executable, and the program loads its shaders and models from there with relative paths.

## Project structure

```
.
├── Learning_OpenGL.sln
├── Learning_OpenGL/
│   ├── Scripts/             C++ source
│   │   ├── main.cpp         Window, input and render loop
│   │   ├── Camera.*         Fly camera
│   │   ├── Shader.*         Shader loading and uniform setting
│   │   ├── Texture.*        Texture loading
│   │   ├── Mesh.*, Model.*, ModelLoader.h   Assimp model loading and drawing
│   │   ├── SceneObject.*    Base class for scene objects
│   │   └── Light/           Directional, point and spot lights
│   └── Resources/           Shaders, textures and models
├── Dependencies/            Third-party headers (GLFW, Assimp, GLM, glad, stb_image)
└── Deployment/              Inno Setup installer script
```

## Credits

- Tutorials by Joey de Vries at [learnopengl.com](https://learnopengl.com/)
- The backpack model is by Berk Gedik, from [Sketchfab](https://sketchfab.com/3d-models/survival-guitar-backpack-low-poly-799f8c4511f84fab8c3f12887f7e6b36). It was modified by Joey de Vries for the Learn OpenGL model loading chapter. See `Resources/Models/backpack/source_attribution.txt`.

## License

Released under the MIT License. See [LICENSE](LICENSE).
