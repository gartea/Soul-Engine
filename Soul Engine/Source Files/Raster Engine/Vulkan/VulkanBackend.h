#pragma once

#include "Utility\Includes\GLFWIncludes.h"
#include "Display\Window\Window.h"
#include "Raster Engine\RasterBackend.h"



class VulkanBackend : public RasterBackend::Backend {
public:
	VulkanBackend();
	~VulkanBackend();

	void Init();
	void CreateWindow(Window&);
private:

};