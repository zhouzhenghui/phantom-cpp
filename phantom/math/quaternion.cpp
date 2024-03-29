#include "phantom/phantom.h"
#include "quaternion.h"
#include "quaternion.hxx"

o_registerNT((phantom, math), (typename), (t_Ty), axis_angle);
o_registerNT((phantom, math), (typename), (t_Ty), quaternion);
o_registerNTI((phantom, math), axis_angle, (float));
o_registerNTI((phantom, math), quaternion, (float));
o_registerNTI((phantom, math), axis_angle, (double));
o_registerNTI((phantom, math), quaternion, (double));

o_namespace_begin(phantom, math)

/** Constants **/
	template<>
	const quaternion<float32> quaternion<float32>::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
	template<>
	const quaternion<float32> quaternion<float32>::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);
	
	template<>
	const quaternion<float64> quaternion<float64>::ZERO(0.0, 0.0, 0.0, 0.0);
	template<>
	const quaternion<float64> quaternion<float64>::IDENTITY(1.0, 0.0, 0.0, 0.0);
o_namespace_end(phantom, math) 
