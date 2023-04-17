#version 450 core

uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;

void main()
{
    float ambient_intensity = 0.1;
    float specular_intensity = 0.5;
    float shininess = 64.0;

    vec3 normal = normalize(v_Normal);
    vec3 light_dir = normalize(v_Position - u_LightPosition);
    float light_intensity = max(dot(normal, -light_dir), 0.0);

    vec3 view_dir = normalize(u_CameraPosition - v_Position);
    vec3 reflect_dir = reflect(light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), shininess);

    vec3 ambient = ambient_intensity * u_ObjectColor;
    vec3 diffuse = light_intensity * u_LightColor;
    vec3 specular = specular_intensity * spec * u_LightColor;

    vec3 result = (ambient + diffuse + specular) * u_ObjectColor;
    gl_FragColor = vec4(result, 1.0);
}