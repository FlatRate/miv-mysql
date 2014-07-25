#pragma once

namespace SDK {
	class Vector {
	public:
		virtual const float& GetX () const = 0;
		virtual const float& GetY () const = 0;
		virtual const float& GetZ () const = 0;
	};
}