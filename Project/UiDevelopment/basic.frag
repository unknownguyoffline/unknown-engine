#version 450 core

in vec2 uv;
out vec4 color;
uniform sampler2D textures[32];

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

float pxRange = 2.0;

float screenPxRange() {
    vec2 unitRange = vec2(pxRange)/vec2(32.f, 32.f);
    vec2 screenTexSize = vec2(1.0)/fwidth(uv);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

void main() {
    vec3 msd = texture(textures[0], uv).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);

    if(opacity > 0.01)
        color = mix(vec4(0), vec4(1.0), opacity);
    else
        discard;
}