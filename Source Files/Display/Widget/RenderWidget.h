#pragma once

#include "Display\Widget\Widget.h"
#include "Metrics.h"
#include "GPGPU\GPURasterBuffer.h"
#include "GPGPU\GPUBuffer.h"
#include "Ray Engine/RayEngine.h"
#include "Photography/Camera/Camera.h"

/* A render widget. */
class RenderWidget : public Widget
{
public:

	/*
	 *    Constructor.
	 *    @param [in,out]	parameter1	If non-null, the first parameter.
	 */

	RenderWidget(Camera*);
	/* Destructor. */
	~RenderWidget();

	/* Draws this object. */
	virtual void Draw();
	/* Recreate data. */
	virtual void RecreateData();

protected:



private:

	/* Size of the current */
	glm::uvec2 currentSize;
	/* Size of the render */
	glm::uvec2 renderSize;

	/* The buffer */
	GPURasterBuffer<glm::vec4> buffer;
	/* The accumulator */
	GPUBuffer<glm::vec4> accumulator;
	/* Information describing the extra */
	GPUBuffer<int> extraData;

	/* The samples */
	float samples;
	/* The camera */
	Camera* camera;
	/* The ray job */
	uint rayJob;

	/* Zero-based index of the counter */
	uint iCounter;
	/* True to integrate */
	bool integrate;
	/* The time */
	double time;
};

