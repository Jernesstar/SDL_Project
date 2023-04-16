#version 450 core

uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;
uniform vec3 u_LightPosition;

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;

void main()
{
    float ambient_strength = 0.1;
    vec3 normal = normalize(v_Normal);
    vec3 light_dir = normalize(v_Position - u_LightPosition);
    float light_intensity = max(dot(normal, -light_dir), 0.0);

    vec3 ambient = ambient_strength * u_ObjectColor;
    vec3 diffuse = light_intensity * u_LightColor;

    vec3 result = (ambient + diffuse) * u_ObjectColor;
    gl_FragColor = vec4(result, 1.0);
}