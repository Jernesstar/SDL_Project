#version 450 core

#define POINT_LIGHTS 4

layout(location = 0) in vec3 v_FragPosition;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TextureCoordinate;

layout(location = 0) out vec4 FragColor;

struct Material {
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};

struct DirectionalLight {
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct PointLight {
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

uniform DirectionalLight u_DirLight;
uniform PointLight u_PointLights[POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 view_dir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 view_dir);

void main()
{
    vec3 normal = normalize(Normal);
    vec3 view_dir = normalize(u_CameraPosition - v_FragPosition);

    vec3 result = vec3(0.0, 0.0, 0.0);
    result = CalcDirLight(dirLight, normal, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(u_PointLights[i], normal, v_FragPosition, view_dir);
    // result += CalcSpotLight(spot_light, normal, FragPos, view_dir);

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(light.direction);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float diff = max(dot(normal, light_dir), 0.0);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_Material.Shininess);

    vec3 ambient  = light.ambient  * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.Specular, v_TextureCoordinate));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(light.position - v_FragPosition);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float diff = max(dot(normal, light_dir), 0.0);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    float dist = length(light.Position - v_FragPosition);
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist));

    vec3 ambient  = light.ambient  * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.Specular, v_TextureCoordinate));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 