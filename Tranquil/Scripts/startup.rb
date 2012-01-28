@scene = Scene.globalScene

$LOAD_PATH.push File.dirname(__FILE__)
require "glmath"

# Setup
def _setup
	@scene.clearColor = vec4(0,0,0,1)
	
	@scene.camera.position = vec4(0, 0, 10, 1)
	@scene.camera.orientation = quat(0, 1, 0, 0)
	@scene.camera.updateMatrix
	
	light = Light.new
	light.position = vec4(0,10,0,1)
	light.ambientColor = vec4(0.2, 0.2, 0.2, 1)
	light.specularColor = vec4(0.1, 0.1, 0.1, 1)
	light.diffuseColor = vec4(0.7, 0.7, 0.7, 1)
	@scene.addLight light
end

# Frame callback
@userFrameCallback = nil
@internalFrameCallbacks = []
# This is meant for use by plugins that need to perform operations on each frame
def _registerFrameCallback(&callback)
	@internalFrameCallbacks.push callback
end
def _frameCallback
	@internalFrameCallbacks.each { |c| c.call }
	@userFrameCallback.call unless @userFrameCallback.nil?
end

def everyFrame(&callback)
	@userFrameCallback = callback
end
