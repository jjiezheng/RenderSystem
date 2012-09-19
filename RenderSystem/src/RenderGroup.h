#ifndef _rendergroup_h_
#define _rendergroup_h_

#include "RenderInstance.h"
#include <vector>

namespace sturm {

	class RenderGroup {
	public:
	private:
		std::vector<RenderInstance> _renderInstances;
	};


} //namespace

#endif