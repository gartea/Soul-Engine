#include "RayJob.cuh"

static uint counter = 0;

__host__ RayJob::RayJob(rayType whatToGet, bool _canChange, float newSamples, Camera _camera) :
	camera(_camera)
{

	type = whatToGet;
	samples = newSamples;
	startIndex = 0;
	canChange = _canChange;
	id = counter++;
}

__host__ RayJob::~RayJob() {

}