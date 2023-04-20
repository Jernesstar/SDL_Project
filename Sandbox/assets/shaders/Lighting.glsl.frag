#version 450 core

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TextureCoordinate;

struct Material
{
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};

uniform vec3 u_CameraPosition;

layout(std140, binding = 1) uniform Light
{
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

layout(binding = 2) uniform Material u_Material;

void main()
{
    vec3 diffuse_color = texture(u_Material.Diffuse, v_TextureCoordinate).xyz;
    vec3 specular_color = texture(u_Material.Specular, v_TextureCoordinate).xyz;

    vec3 normal = normalize(v_Normal);
    vec3 light_dir = normalize(v_Position - Position);
    float diff = max(dot(normal, -light_dir), 0.0);

    vec3 view_dir = normalize(u_CameraPosition - v_Position);
    vec3 reflect_dir = reflect(light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_Material.Shininess);

    vec3 ambient  = Ambient  * diffuse_color;
    vec3 diffuse  = Diffuse  * (diff * diffuse_color);
    vec3 specular = Specular * (spec * specular_color);

    vec3 result = ambient + diffuse + specular;
    gl_FragColor = vec4(result, 1.0);
}