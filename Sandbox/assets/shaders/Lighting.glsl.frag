#version 450 core

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TextureCoordinate;

layout(location = 0) out vec4 FragColor;

struct Material
{
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};

// struct Light
// {
//     vec3 Position;
//     vec3 Ambient;
//     vec3 Diffuse;
//     vec3 Specular;
// };

struct PointLight
{
    vec3 Position;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;
};

uniform vec3 u_CameraPosition;

uniform Material u_Material;
// uniform Light u_Light;
uniform PointLight u_Light;

void main()
{
    vec3 diffuse_color = texture(u_Material.Diffuse, v_TextureCoordinate).rgb;
    vec3 specular_color = texture(u_Material.Specular, v_TextureCoordinate).rgb;

    vec3 normal = normalize(v_Normal);
    vec3 light_dir = normalize(v_Position - u_Light.Position);
    float diff = max(dot(normal, -light_dir), 0.0);

    vec3 view_dir = normalize(u_CameraPosition - v_Position);
    vec3 reflect_dir = reflect(light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_Material.Shininess);

    float dist = length(u_Light.Position - v_Position);
    float attenuation = 1.0 / (u_Light.Constant + u_Light.Linear * dist + u_Light.Quadratic * (dist * dist));

    vec3 ambient  = u_Light.Ambient  * diffuse_color;
    vec3 diffuse  = u_Light.Diffuse  * (diff * diffuse_color);
    vec3 specular = u_Light.Specular * (spec * specular_color);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
