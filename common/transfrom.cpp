#include "transfrom.h"
#include "helper.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::SetTransformation(vec3 _pos, vec3 _rot, vec3 _scale)
{
	transform = mat4(1);

	transform = translate(transform, _pos);
	transform = rotate(transform, _rot.x, vec3(1.0, 0.0, 0.0));
	transform = rotate(transform, _rot.y, vec3(0.0, 1.0, 0.0));
	transform = rotate(transform, _rot.z, vec3(0.0, 0.0, 1.0));
	transform = scale(transform, vec3(_scale));

}

void Transform::Translate(vec3 _pos)
{
	transform = translate(transform, _pos);
}

void Transform::Rotate(vec3 _axis, float32 angle)
{
	transform = rotate(transform, angle, _axis);
}

void Transform::Scale(vec3 _scale)
{
	transform = scale(transform, vec3(_scale));
}

mat4 Transform::GetTransfrom()
{
	return transform;
}

void Transform::ResetTransfrom()
{
	transform = mat4(1);
}

