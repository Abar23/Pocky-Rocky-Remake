#pragma once

#include "Vec2.h"
#include "Vec3.h"

template <typename T>
class alignas(16) Vec4
{
public:
	union
	{
		std::array<T, 4> data;

		struct
		{
			T x, y, z, w;
		};

		Swizzle<Vec2, T, 4, 0, 0> xx;
		Swizzle<Vec2, T, 4, 0, 1> xy;
		Swizzle<Vec2, T, 4, 0, 2> xz;
		Swizzle<Vec2, T, 4, 0, 3> xw;
		Swizzle<Vec2, T, 4, 1, 0> yx;
		Swizzle<Vec2, T, 4, 1, 1> yy;
		Swizzle<Vec2, T, 4, 1, 2> yz;
		Swizzle<Vec2, T, 4, 1, 3> yw;
		Swizzle<Vec2, T, 4, 2, 0> zx;
		Swizzle<Vec2, T, 4, 2, 1> zy;
		Swizzle<Vec2, T, 4, 2, 2> zz;
		Swizzle<Vec2, T, 4, 2, 3> zw;
		Swizzle<Vec2, T, 4, 3, 0> wx;
		Swizzle<Vec2, T, 4, 3, 1> wy;
		Swizzle<Vec2, T, 4, 3, 2> wz;
		Swizzle<Vec2, T, 4, 3, 3> ww;

		Swizzle<Vec3, T, 4, 0, 0, 0> xxx;
		Swizzle<Vec3, T, 4, 0, 0, 1> xxy;
		Swizzle<Vec3, T, 4, 0, 0, 2> xxz;
		Swizzle<Vec3, T, 4, 0, 0, 3> xxw;
		Swizzle<Vec3, T, 4, 0, 1, 0> xyx;
		Swizzle<Vec3, T, 4, 0, 1, 1> xyy;
		Swizzle<Vec3, T, 4, 0, 1, 2> xyz;
		Swizzle<Vec3, T, 4, 0, 1, 3> xyw;
		Swizzle<Vec3, T, 4, 0, 2, 0> xzx;
		Swizzle<Vec3, T, 4, 0, 2, 1> xzy;
		Swizzle<Vec3, T, 4, 0, 2, 2> xzz;
		Swizzle<Vec3, T, 4, 0, 2, 3> xzw;
		Swizzle<Vec3, T, 4, 0, 3, 0> xwx;
		Swizzle<Vec3, T, 4, 0, 3, 1> xwy;
		Swizzle<Vec3, T, 4, 0, 3, 2> xwz;
		Swizzle<Vec3, T, 4, 0, 3, 3> xww;
		Swizzle<Vec3, T, 4, 1, 0, 0> yxx;
		Swizzle<Vec3, T, 4, 1, 0, 1> yxy;
		Swizzle<Vec3, T, 4, 1, 0, 2> yxz;
		Swizzle<Vec3, T, 4, 1, 0, 3> yxw;
		Swizzle<Vec3, T, 4, 1, 1, 0> yyx;
		Swizzle<Vec3, T, 4, 1, 1, 1> yyy;
		Swizzle<Vec3, T, 4, 1, 1, 2> yyz;
		Swizzle<Vec3, T, 4, 1, 1, 3> yyw;
		Swizzle<Vec3, T, 4, 1, 2, 0> yzx;
		Swizzle<Vec3, T, 4, 1, 2, 1> yzy;
		Swizzle<Vec3, T, 4, 1, 2, 2> yzz;
		Swizzle<Vec3, T, 4, 1, 2, 3> yzw;
		Swizzle<Vec3, T, 4, 1, 3, 0> ywx;
		Swizzle<Vec3, T, 4, 1, 3, 1> ywy;
		Swizzle<Vec3, T, 4, 1, 3, 2> ywz;
		Swizzle<Vec3, T, 4, 1, 3, 3> yww;
		Swizzle<Vec3, T, 4, 2, 0, 0> zxx;
		Swizzle<Vec3, T, 4, 2, 0, 1> zxy;
		Swizzle<Vec3, T, 4, 2, 0, 2> zxz;
		Swizzle<Vec3, T, 4, 2, 0, 3> zxw;
		Swizzle<Vec3, T, 4, 2, 1, 0> zyx;
		Swizzle<Vec3, T, 4, 2, 1, 1> zyy;
		Swizzle<Vec3, T, 4, 2, 1, 2> zyz;
		Swizzle<Vec3, T, 4, 2, 1, 3> zyw;
		Swizzle<Vec3, T, 4, 2, 2, 0> zzx;
		Swizzle<Vec3, T, 4, 2, 2, 1> zzy;
		Swizzle<Vec3, T, 4, 2, 2, 2> zzz;
		Swizzle<Vec3, T, 4, 2, 2, 3> zzw;
		Swizzle<Vec3, T, 4, 2, 3, 0> zwx;
		Swizzle<Vec3, T, 4, 2, 3, 1> zwy;
		Swizzle<Vec3, T, 4, 2, 3, 2> zwz;
		Swizzle<Vec3, T, 4, 2, 3, 3> zww;
		Swizzle<Vec3, T, 4, 3, 0, 0> wxx;
		Swizzle<Vec3, T, 4, 3, 0, 1> wxy;
		Swizzle<Vec3, T, 4, 3, 0, 2> wxz;
		Swizzle<Vec3, T, 4, 3, 0, 3> wxw;
		Swizzle<Vec3, T, 4, 3, 1, 0> wyx;
		Swizzle<Vec3, T, 4, 3, 1, 1> wyy;
		Swizzle<Vec3, T, 4, 3, 1, 2> wyz;
		Swizzle<Vec3, T, 4, 3, 1, 3> wyw;
		Swizzle<Vec3, T, 4, 3, 2, 0> wzx;
		Swizzle<Vec3, T, 4, 3, 2, 1> wzy;
		Swizzle<Vec3, T, 4, 3, 2, 2> wzz;
		Swizzle<Vec3, T, 4, 3, 2, 3> wzw;
		Swizzle<Vec3, T, 4, 3, 3, 0> wwx;
		Swizzle<Vec3, T, 4, 3, 3, 1> wwy;
		Swizzle<Vec3, T, 4, 3, 3, 2> wwz;
		Swizzle<Vec3, T, 4, 3, 3, 3> www;

		Swizzle<Vec4, T, 4, 0, 0, 0, 0> xxxx;
		Swizzle<Vec4, T, 4, 0, 0, 0, 1> xxxy;
		Swizzle<Vec4, T, 4, 0, 0, 0, 2> xxxz;
		Swizzle<Vec4, T, 4, 0, 0, 0, 3> xxxw;
		Swizzle<Vec4, T, 4, 0, 0, 1, 0> xxyx;
		Swizzle<Vec4, T, 4, 0, 0, 1, 1> xxyy;
		Swizzle<Vec4, T, 4, 0, 0, 1, 2> xxyz;
		Swizzle<Vec4, T, 4, 0, 0, 1, 3> xxyw;
		Swizzle<Vec4, T, 4, 0, 0, 2, 0> xxzx;
		Swizzle<Vec4, T, 4, 0, 0, 2, 1> xxzy;
		Swizzle<Vec4, T, 4, 0, 0, 2, 2> xxzz;
		Swizzle<Vec4, T, 4, 0, 0, 2, 3> xxzw;
		Swizzle<Vec4, T, 4, 0, 0, 3, 0> xxwx;
		Swizzle<Vec4, T, 4, 0, 0, 3, 1> xxwy;
		Swizzle<Vec4, T, 4, 0, 0, 3, 2> xxwz;
		Swizzle<Vec4, T, 4, 0, 0, 3, 3> xxww;
		Swizzle<Vec4, T, 4, 0, 1, 0, 0> xyxx;
		Swizzle<Vec4, T, 4, 0, 1, 0, 1> xyxy;
		Swizzle<Vec4, T, 4, 0, 1, 0, 2> xyxz;
		Swizzle<Vec4, T, 4, 0, 1, 0, 3> xyxw;
		Swizzle<Vec4, T, 4, 0, 1, 1, 0> xyyx;
		Swizzle<Vec4, T, 4, 0, 1, 1, 1> xyyy;
		Swizzle<Vec4, T, 4, 0, 1, 1, 2> xyyz;
		Swizzle<Vec4, T, 4, 0, 1, 1, 3> xyyw;
		Swizzle<Vec4, T, 4, 0, 1, 2, 0> xyzx;
		Swizzle<Vec4, T, 4, 0, 1, 2, 1> xyzy;
		Swizzle<Vec4, T, 4, 0, 1, 2, 2> xyzz;
		Swizzle<Vec4, T, 4, 0, 1, 2, 3> xyzw;
		Swizzle<Vec4, T, 4, 0, 1, 3, 0> xywx;
		Swizzle<Vec4, T, 4, 0, 1, 3, 1> xywy;
		Swizzle<Vec4, T, 4, 0, 1, 3, 2> xywz;
		Swizzle<Vec4, T, 4, 0, 1, 3, 3> xyww;
		Swizzle<Vec4, T, 4, 0, 2, 0, 0> xzxx;
		Swizzle<Vec4, T, 4, 0, 2, 0, 1> xzxy;
		Swizzle<Vec4, T, 4, 0, 2, 0, 2> xzxz;
		Swizzle<Vec4, T, 4, 0, 2, 0, 3> xzxw;
		Swizzle<Vec4, T, 4, 0, 2, 1, 0> xzyx;
		Swizzle<Vec4, T, 4, 0, 2, 1, 1> xzyy;
		Swizzle<Vec4, T, 4, 0, 2, 1, 2> xzyz;
		Swizzle<Vec4, T, 4, 0, 2, 1, 3> xzyw;
		Swizzle<Vec4, T, 4, 0, 2, 2, 0> xzzx;
		Swizzle<Vec4, T, 4, 0, 2, 2, 1> xzzy;
		Swizzle<Vec4, T, 4, 0, 2, 2, 2> xzzz;
		Swizzle<Vec4, T, 4, 0, 2, 2, 3> xzzw;
		Swizzle<Vec4, T, 4, 0, 2, 3, 0> xzwx;
		Swizzle<Vec4, T, 4, 0, 2, 3, 1> xzwy;
		Swizzle<Vec4, T, 4, 0, 2, 3, 2> xzwz;
		Swizzle<Vec4, T, 4, 0, 2, 3, 3> xzww;
		Swizzle<Vec4, T, 4, 0, 3, 0, 0> xwxx;
		Swizzle<Vec4, T, 4, 0, 3, 0, 1> xwxy;
		Swizzle<Vec4, T, 4, 0, 3, 0, 2> xwxz;
		Swizzle<Vec4, T, 4, 0, 3, 0, 3> xwxw;
		Swizzle<Vec4, T, 4, 0, 3, 1, 0> xwyx;
		Swizzle<Vec4, T, 4, 0, 3, 1, 1> xwyy;
		Swizzle<Vec4, T, 4, 0, 3, 1, 2> xwyz;
		Swizzle<Vec4, T, 4, 0, 3, 1, 3> xwyw;
		Swizzle<Vec4, T, 4, 0, 3, 2, 0> xwzx;
		Swizzle<Vec4, T, 4, 0, 3, 2, 1> xwzy;
		Swizzle<Vec4, T, 4, 0, 3, 2, 2> xwzz;
		Swizzle<Vec4, T, 4, 0, 3, 2, 3> xwzw;
		Swizzle<Vec4, T, 4, 0, 3, 3, 0> xwwx;
		Swizzle<Vec4, T, 4, 0, 3, 3, 1> xwwy;
		Swizzle<Vec4, T, 4, 0, 3, 3, 2> xwwz;
		Swizzle<Vec4, T, 4, 0, 3, 3, 3> xwww;
		Swizzle<Vec4, T, 4, 1, 0, 0, 0> yxxx;
		Swizzle<Vec4, T, 4, 1, 0, 0, 1> yxxy;
		Swizzle<Vec4, T, 4, 1, 0, 0, 2> yxxz;
		Swizzle<Vec4, T, 4, 1, 0, 0, 3> yxxw;
		Swizzle<Vec4, T, 4, 1, 0, 1, 0> yxyx;
		Swizzle<Vec4, T, 4, 1, 0, 1, 1> yxyy;
		Swizzle<Vec4, T, 4, 1, 0, 1, 2> yxyz;
		Swizzle<Vec4, T, 4, 1, 0, 1, 3> yxyw;
		Swizzle<Vec4, T, 4, 1, 0, 2, 0> yxzx;
		Swizzle<Vec4, T, 4, 1, 0, 2, 1> yxzy;
		Swizzle<Vec4, T, 4, 1, 0, 2, 2> yxzz;
		Swizzle<Vec4, T, 4, 1, 0, 2, 3> yxzw;
		Swizzle<Vec4, T, 4, 1, 0, 3, 0> yxwx;
		Swizzle<Vec4, T, 4, 1, 0, 3, 1> yxwy;
		Swizzle<Vec4, T, 4, 1, 0, 3, 2> yxwz;
		Swizzle<Vec4, T, 4, 1, 0, 3, 3> yxww;
		Swizzle<Vec4, T, 4, 1, 1, 0, 0> yyxx;
		Swizzle<Vec4, T, 4, 1, 1, 0, 1> yyxy;
		Swizzle<Vec4, T, 4, 1, 1, 0, 2> yyxz;
		Swizzle<Vec4, T, 4, 1, 1, 0, 3> yyxw;
		Swizzle<Vec4, T, 4, 1, 1, 1, 0> yyyx;
		Swizzle<Vec4, T, 4, 1, 1, 1, 1> yyyy;
		Swizzle<Vec4, T, 4, 1, 1, 1, 2> yyyz;
		Swizzle<Vec4, T, 4, 1, 1, 1, 3> yyyw;
		Swizzle<Vec4, T, 4, 1, 1, 2, 0> yyzx;
		Swizzle<Vec4, T, 4, 1, 1, 2, 1> yyzy;
		Swizzle<Vec4, T, 4, 1, 1, 2, 2> yyzz;
		Swizzle<Vec4, T, 4, 1, 1, 2, 3> yyzw;
		Swizzle<Vec4, T, 4, 1, 1, 3, 0> yywx;
		Swizzle<Vec4, T, 4, 1, 1, 3, 1> yywy;
		Swizzle<Vec4, T, 4, 1, 1, 3, 2> yywz;
		Swizzle<Vec4, T, 4, 1, 1, 3, 3> yyww;
		Swizzle<Vec4, T, 4, 1, 2, 0, 0> yzxx;
		Swizzle<Vec4, T, 4, 1, 2, 0, 1> yzxy;
		Swizzle<Vec4, T, 4, 1, 2, 0, 2> yzxz;
		Swizzle<Vec4, T, 4, 1, 2, 0, 3> yzxw;
		Swizzle<Vec4, T, 4, 1, 2, 1, 0> yzyx;
		Swizzle<Vec4, T, 4, 1, 2, 1, 1> yzyy;
		Swizzle<Vec4, T, 4, 1, 2, 1, 2> yzyz;
		Swizzle<Vec4, T, 4, 1, 2, 1, 3> yzyw;
		Swizzle<Vec4, T, 4, 1, 2, 2, 0> yzzx;
		Swizzle<Vec4, T, 4, 1, 2, 2, 1> yzzy;
		Swizzle<Vec4, T, 4, 1, 2, 2, 2> yzzz;
		Swizzle<Vec4, T, 4, 1, 2, 2, 3> yzzw;
		Swizzle<Vec4, T, 4, 1, 2, 3, 0> yzwx;
		Swizzle<Vec4, T, 4, 1, 2, 3, 1> yzwy;
		Swizzle<Vec4, T, 4, 1, 2, 3, 2> yzwz;
		Swizzle<Vec4, T, 4, 1, 2, 3, 3> yzww;
		Swizzle<Vec4, T, 4, 1, 3, 0, 0> ywxx;
		Swizzle<Vec4, T, 4, 1, 3, 0, 1> ywxy;
		Swizzle<Vec4, T, 4, 1, 3, 0, 2> ywxz;
		Swizzle<Vec4, T, 4, 1, 3, 0, 3> ywxw;
		Swizzle<Vec4, T, 4, 1, 3, 1, 0> ywyx;
		Swizzle<Vec4, T, 4, 1, 3, 1, 1> ywyy;
		Swizzle<Vec4, T, 4, 1, 3, 1, 2> ywyz;
		Swizzle<Vec4, T, 4, 1, 3, 1, 3> ywyw;
		Swizzle<Vec4, T, 4, 1, 3, 2, 0> ywzx;
		Swizzle<Vec4, T, 4, 1, 3, 2, 1> ywzy;
		Swizzle<Vec4, T, 4, 1, 3, 2, 2> ywzz;
		Swizzle<Vec4, T, 4, 1, 3, 2, 3> ywzw;
		Swizzle<Vec4, T, 4, 1, 3, 3, 0> ywwx;
		Swizzle<Vec4, T, 4, 1, 3, 3, 1> ywwy;
		Swizzle<Vec4, T, 4, 1, 3, 3, 2> ywwz;
		Swizzle<Vec4, T, 4, 1, 3, 3, 3> ywww;
		Swizzle<Vec4, T, 4, 2, 0, 0, 0> zxxx;
		Swizzle<Vec4, T, 4, 2, 0, 0, 1> zxxy;
		Swizzle<Vec4, T, 4, 2, 0, 0, 2> zxxz;
		Swizzle<Vec4, T, 4, 2, 0, 0, 3> zxxw;
		Swizzle<Vec4, T, 4, 2, 0, 1, 0> zxyx;
		Swizzle<Vec4, T, 4, 2, 0, 1, 1> zxyy;
		Swizzle<Vec4, T, 4, 2, 0, 1, 2> zxyz;
		Swizzle<Vec4, T, 4, 2, 0, 1, 3> zxyw;
		Swizzle<Vec4, T, 4, 2, 0, 2, 0> zxzx;
		Swizzle<Vec4, T, 4, 2, 0, 2, 1> zxzy;
		Swizzle<Vec4, T, 4, 2, 0, 2, 2> zxzz;
		Swizzle<Vec4, T, 4, 2, 0, 2, 3> zxzw;
		Swizzle<Vec4, T, 4, 2, 0, 3, 0> zxwx;
		Swizzle<Vec4, T, 4, 2, 0, 3, 1> zxwy;
		Swizzle<Vec4, T, 4, 2, 0, 3, 2> zxwz;
		Swizzle<Vec4, T, 4, 2, 0, 3, 3> zxww;
		Swizzle<Vec4, T, 4, 2, 1, 0, 0> zyxx;
		Swizzle<Vec4, T, 4, 2, 1, 0, 1> zyxy;
		Swizzle<Vec4, T, 4, 2, 1, 0, 2> zyxz;
		Swizzle<Vec4, T, 4, 2, 1, 0, 3> zyxw;
		Swizzle<Vec4, T, 4, 2, 1, 1, 0> zyyx;
		Swizzle<Vec4, T, 4, 2, 1, 1, 1> zyyy;
		Swizzle<Vec4, T, 4, 2, 1, 1, 2> zyyz;
		Swizzle<Vec4, T, 4, 2, 1, 1, 3> zyyw;
		Swizzle<Vec4, T, 4, 2, 1, 2, 0> zyzx;
		Swizzle<Vec4, T, 4, 2, 1, 2, 1> zyzy;
		Swizzle<Vec4, T, 4, 2, 1, 2, 2> zyzz;
		Swizzle<Vec4, T, 4, 2, 1, 2, 3> zyzw;
		Swizzle<Vec4, T, 4, 2, 1, 3, 0> zywx;
		Swizzle<Vec4, T, 4, 2, 1, 3, 1> zywy;
		Swizzle<Vec4, T, 4, 2, 1, 3, 2> zywz;
		Swizzle<Vec4, T, 4, 2, 1, 3, 3> zyww;
		Swizzle<Vec4, T, 4, 2, 2, 0, 0> zzxx;
		Swizzle<Vec4, T, 4, 2, 2, 0, 1> zzxy;
		Swizzle<Vec4, T, 4, 2, 2, 0, 2> zzxz;
		Swizzle<Vec4, T, 4, 2, 2, 0, 3> zzxw;
		Swizzle<Vec4, T, 4, 2, 2, 1, 0> zzyx;
		Swizzle<Vec4, T, 4, 2, 2, 1, 1> zzyy;
		Swizzle<Vec4, T, 4, 2, 2, 1, 2> zzyz;
		Swizzle<Vec4, T, 4, 2, 2, 1, 3> zzyw;
		Swizzle<Vec4, T, 4, 2, 2, 2, 0> zzzx;
		Swizzle<Vec4, T, 4, 2, 2, 2, 1> zzzy;
		Swizzle<Vec4, T, 4, 2, 2, 2, 2> zzzz;
		Swizzle<Vec4, T, 4, 2, 2, 2, 3> zzzw;
		Swizzle<Vec4, T, 4, 2, 2, 3, 0> zzwx;
		Swizzle<Vec4, T, 4, 2, 2, 3, 1> zzwy;
		Swizzle<Vec4, T, 4, 2, 2, 3, 2> zzwz;
		Swizzle<Vec4, T, 4, 2, 2, 3, 3> zzww;
		Swizzle<Vec4, T, 4, 2, 3, 0, 0> zwxx;
		Swizzle<Vec4, T, 4, 2, 3, 0, 1> zwxy;
		Swizzle<Vec4, T, 4, 2, 3, 0, 2> zwxz;
		Swizzle<Vec4, T, 4, 2, 3, 0, 3> zwxw;
		Swizzle<Vec4, T, 4, 2, 3, 1, 0> zwyx;
		Swizzle<Vec4, T, 4, 2, 3, 1, 1> zwyy;
		Swizzle<Vec4, T, 4, 2, 3, 1, 2> zwyz;
		Swizzle<Vec4, T, 4, 2, 3, 1, 3> zwyw;
		Swizzle<Vec4, T, 4, 2, 3, 2, 0> zwzx;
		Swizzle<Vec4, T, 4, 2, 3, 2, 1> zwzy;
		Swizzle<Vec4, T, 4, 2, 3, 2, 2> zwzz;
		Swizzle<Vec4, T, 4, 2, 3, 2, 3> zwzw;
		Swizzle<Vec4, T, 4, 2, 3, 3, 0> zwwx;
		Swizzle<Vec4, T, 4, 2, 3, 3, 1> zwwy;
		Swizzle<Vec4, T, 4, 2, 3, 3, 2> zwwz;
		Swizzle<Vec4, T, 4, 2, 3, 3, 3> zwww;
		Swizzle<Vec4, T, 4, 3, 0, 0, 0> wxxx;
		Swizzle<Vec4, T, 4, 3, 0, 0, 1> wxxy;
		Swizzle<Vec4, T, 4, 3, 0, 0, 2> wxxz;
		Swizzle<Vec4, T, 4, 3, 0, 0, 3> wxxw;
		Swizzle<Vec4, T, 4, 3, 0, 1, 0> wxyx;
		Swizzle<Vec4, T, 4, 3, 0, 1, 1> wxyy;
		Swizzle<Vec4, T, 4, 3, 0, 1, 2> wxyz;
		Swizzle<Vec4, T, 4, 3, 0, 1, 3> wxyw;
		Swizzle<Vec4, T, 4, 3, 0, 2, 0> wxzx;
		Swizzle<Vec4, T, 4, 3, 0, 2, 1> wxzy;
		Swizzle<Vec4, T, 4, 3, 0, 2, 2> wxzz;
		Swizzle<Vec4, T, 4, 3, 0, 2, 3> wxzw;
		Swizzle<Vec4, T, 4, 3, 0, 3, 0> wxwx;
		Swizzle<Vec4, T, 4, 3, 0, 3, 1> wxwy;
		Swizzle<Vec4, T, 4, 3, 0, 3, 2> wxwz;
		Swizzle<Vec4, T, 4, 3, 0, 3, 3> wxww;
		Swizzle<Vec4, T, 4, 3, 1, 0, 0> wyxx;
		Swizzle<Vec4, T, 4, 3, 1, 0, 1> wyxy;
		Swizzle<Vec4, T, 4, 3, 1, 0, 2> wyxz;
		Swizzle<Vec4, T, 4, 3, 1, 0, 3> wyxw;
		Swizzle<Vec4, T, 4, 3, 1, 1, 0> wyyx;
		Swizzle<Vec4, T, 4, 3, 1, 1, 1> wyyy;
		Swizzle<Vec4, T, 4, 3, 1, 1, 2> wyyz;
		Swizzle<Vec4, T, 4, 3, 1, 1, 3> wyyw;
		Swizzle<Vec4, T, 4, 3, 1, 2, 0> wyzx;
		Swizzle<Vec4, T, 4, 3, 1, 2, 1> wyzy;
		Swizzle<Vec4, T, 4, 3, 1, 2, 2> wyzz;
		Swizzle<Vec4, T, 4, 3, 1, 2, 3> wyzw;
		Swizzle<Vec4, T, 4, 3, 1, 3, 0> wywx;
		Swizzle<Vec4, T, 4, 3, 1, 3, 1> wywy;
		Swizzle<Vec4, T, 4, 3, 1, 3, 2> wywz;
		Swizzle<Vec4, T, 4, 3, 1, 3, 3> wyww;
		Swizzle<Vec4, T, 4, 3, 2, 0, 0> wzxx;
		Swizzle<Vec4, T, 4, 3, 2, 0, 1> wzxy;
		Swizzle<Vec4, T, 4, 3, 2, 0, 2> wzxz;
		Swizzle<Vec4, T, 4, 3, 2, 0, 3> wzxw;
		Swizzle<Vec4, T, 4, 3, 2, 1, 0> wzyx;
		Swizzle<Vec4, T, 4, 3, 2, 1, 1> wzyy;
		Swizzle<Vec4, T, 4, 3, 2, 1, 2> wzyz;
		Swizzle<Vec4, T, 4, 3, 2, 1, 3> wzyw;
		Swizzle<Vec4, T, 4, 3, 2, 2, 0> wzzx;
		Swizzle<Vec4, T, 4, 3, 2, 2, 1> wzzy;
		Swizzle<Vec4, T, 4, 3, 2, 2, 2> wzzz;
		Swizzle<Vec4, T, 4, 3, 2, 2, 3> wzzw;
		Swizzle<Vec4, T, 4, 3, 2, 3, 0> wzwx;
		Swizzle<Vec4, T, 4, 3, 2, 3, 1> wzwy;
		Swizzle<Vec4, T, 4, 3, 2, 3, 2> wzwz;
		Swizzle<Vec4, T, 4, 3, 2, 3, 3> wzww;
		Swizzle<Vec4, T, 4, 3, 3, 0, 0> wwxx;
		Swizzle<Vec4, T, 4, 3, 3, 0, 1> wwxy;
		Swizzle<Vec4, T, 4, 3, 3, 0, 2> wwxz;
		Swizzle<Vec4, T, 4, 3, 3, 0, 3> wwxw;
		Swizzle<Vec4, T, 4, 3, 3, 1, 0> wwyx;
		Swizzle<Vec4, T, 4, 3, 3, 1, 1> wwyy;
		Swizzle<Vec4, T, 4, 3, 3, 1, 2> wwyz;
		Swizzle<Vec4, T, 4, 3, 3, 1, 3> wwyw;
		Swizzle<Vec4, T, 4, 3, 3, 2, 0> wwzx;
		Swizzle<Vec4, T, 4, 3, 3, 2, 1> wwzy;
		Swizzle<Vec4, T, 4, 3, 3, 2, 2> wwzz;
		Swizzle<Vec4, T, 4, 3, 3, 2, 3> wwzw;
		Swizzle<Vec4, T, 4, 3, 3, 3, 0> wwwx;
		Swizzle<Vec4, T, 4, 3, 3, 3, 1> wwwy;
		Swizzle<Vec4, T, 4, 3, 3, 3, 2> wwwz;
		Swizzle<Vec4, T, 4, 3, 3, 3, 3> wwww;
	};

	Vec4();
	Vec4(const Vec4<T>& vector);
	Vec4(std::initializer_list<T> args);
	Vec4(const T x, const T y, const T z, const T w);
	Vec4(const T x, const T y, const T z);
	Vec4(const T scalar);

	~Vec4() = default;

	T Magnitude() const;
	T SqrMagnitude() const;
	Vec4<T> Normalized() const;
	Vec4<T>& Normalize();
	Vec4<T> Renormalized() const;
	Vec4<T>& Renormalize();
	Vec4<T> Negated() const;
	Vec4<T>& Negate();

	static T Dot(const Vec4<T>& leftVector, const Vec4<T>& rightVector);
	static Vec4<T> Lerp(const Vec4<T>& leftVector, const Vec4<T>& rightVector, const T t);
	static Vec4<T> Zero();

	Vec4<T>& operator=(const Vec4<T>& vector);
	Vec4<T>& operator+=(const Vec4<T>& vector);
	Vec4<T>& operator-=(const Vec4<T>& vector);

	__forceinline Vec4& operator*=(const T scalar);
	Vec4& operator/=(const T scalar);

	friend bool operator==(const Vec4<T>& leftVector, const Vec4<T>& rightVector)
	{
		return NearEquals(leftVector.x, rightVector.x) &&
			NearEquals(leftVector.y, rightVector.y) &&
			NearEquals(leftVector.z, rightVector.z) &&
			NearEquals(leftVector.w, rightVector.w);
	}

	friend bool operator!=(const Vec4<T>& leftVector, const Vec4<T>& rightVector)
	{
		return !(leftVector == rightVector);
	}

	friend Vec4<T> operator+(const Vec4<T>& leftVector, const Vec4<T>& rightVector)
	{
		Vec4<T> leftVectorCopy = leftVector;
		return leftVectorCopy += rightVector;
	}

	friend Vec4<T> operator-(const Vec4<T>& leftVector, const Vec4<T>& rightVector)
	{
		Vec4<T> leftVectorCopy = leftVector;
		return leftVectorCopy -= rightVector;
	}

	friend Vec4<T> operator*(const Vec4<T>& vector, const T scalar)
	{
		Vec4<T> vectorCopy = vector;
		return vectorCopy *= scalar;
	}

	friend Vec4<T> operator*(const T scalar, const Vec4<T>& vector)
	{
		Vec4<T> vectorCopy = vector;
		return vectorCopy *= scalar;
	}

	friend Vec4<T> operator/(const Vec4<T>& vector, const T scalar)
	{
		Vec4<T> vectorCopy = vector;
		return vectorCopy /= scalar;
	}

	friend Vec4<T> operator/(const T scalar, const Vec4<T>& vector)
	{
		Vec4<T> vectorCopy = vector;
		return vectorCopy /= scalar;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vec4<T>& vector)
	{
		stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}
};

using ivec4 = Vec4<int>;
using uvec4 = Vec4<unsigned int>;
using vec4 = Vec4<float>;
using dvec4 = Vec4<double>;

#include "Vec4.inl"
