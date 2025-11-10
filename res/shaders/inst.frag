#version 330 core
layout(location = 0) out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_WorldPos; // provided by vertex shader

uniform vec2 u_LightPos;    // XY world coords
uniform vec3 u_LightColor;
uniform float u_LightRadius; // must be > 0

void main()
{
    float radius = max(u_LightRadius, 0.0001);

    float dist = length(v_WorldPos.xy - u_LightPos);

    float t = clamp(dist / radius, 0.0, 1.0);
    float intensity = 1.0 - smoothstep(0.0, 1.0, t);

    vec3 ambient = vec3(0.15); // tweak ambient
    vec3 lit = v_Color.rgb * (ambient + u_LightColor * intensity);

    FragColor = vec4(lit, v_Color.a);
}