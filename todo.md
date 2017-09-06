#Todo

##Application
- Make framebuffer resize callbacks use `glm::ivec2`

##ECS
- Less tedious `getComponent()` method

##Framebuffers
- Fix occasional flickering on framebuffer resize
- GBuffer

##Player
- Limit vertical viewing angles

##Renderer
- Load normal matrix uniform correctly adjusted for scaled objects [link](https://learnopengl.com/#!Lighting/Basic-Lighting)

#Completed

##Framebuffers
- Framebuffer manager
	- Clear automatically on each frame
	- ImGUI browser/viewer
	- Resize with viewport
