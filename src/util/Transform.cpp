// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

mat3 Transform::rotate(const float degrees, const vec3& axis) {
    float x = axis.x,
        y = axis.y,
        z = axis.z,
        cosine = cos(degrees / 180 * pi),
        sine = sin(degrees / 180 * pi),
        a = cosine + x * x * (1 - cosine),
        b = x * y * (1 - cosine) - z * sine,
        c = x * z * (1 - cosine) + y * sine,
        d = y * x * (1 - cosine) + z * sine,
        e = cosine + y * y * (1 - cosine),
        f = y * z * (1 - cosine) - x * sine,
        g = z * x * (1 - cosine) - y * sine,
        h = z * y * (1 - cosine) + x * sine,
        i = cosine + z * z * (1 - cosine);
    return mat3(a, d, g, b, e, h, c, f, i);
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
    mat3 rotationMatrix = rotate(degrees, up);
    eye = rotationMatrix * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
    vec3 left = normalize(cross(eye, up));
    mat3 rotation = rotate(degrees, left);
    up = rotation * up;
    eye = rotation * eye;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
    vec3 z = normalize(eye - center),
         y = normalize(up),
         x = normalize(cross(y, z));
    return transpose(mat4(x.x, x.y, x.z, -dot(x, eye),
                          y.x, y.y, y.z, -dot(y, eye),
                          z.x, z.y, z.z, -dot(z, eye),
                          0, 0, 0, 1));
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar) {
    float theta = fovy * pi / 360,
          d = cos(theta) / sin(theta),
          A = (zFar + zNear) / (zNear - zFar),
          B = 2 * zFar * zNear / (zNear - zFar);
    return transpose(mat4(d / aspect, 0, 0, 0,
                          0, d, 0, 0,
                          0, 0, A, B,
                          0, 0, -1, 0));
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
    return mat4(sx, 0, 0, 0,
                0, sy, 0, 0,
                0, 0, sz, 0,
                0, 0, 0, 1);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
    return mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                tx, ty, tz, 1);
}

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) {
    vec3 x = glm::cross(up,zvec);
    vec3 y = glm::cross(zvec,x);
    vec3 ret = glm::normalize(y);
    return ret;
}


Transform::Transform() {

}

Transform::~Transform() {

}
