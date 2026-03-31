#pragma once

namespace snd3D {
	class App; // Forward declaration to avoid circular include between App and Callbacks

	class Callbacks {
		public:
			Callbacks(App* app);

		private:
			App* app;
	};
}
