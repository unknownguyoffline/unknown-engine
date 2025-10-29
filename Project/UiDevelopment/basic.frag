// Fragment shader (msdf.frag)
#version 450 core

in vec2 uv;
out vec4 fragColor;

uniform sampler2D textures[32];   // MSDF atlas
float uPxRange = 8.0;     // the "range" in pixels encoded into MSDF atlas

// Robust median of three floats
float median3(float a, float b, float c) 
{
    // stable and branch-friendly
    return a + b + c - min(min(a,b), c) - max(max(a,b), c);
}

void main() {
    vec4 uColor = vec4(1.0);
    // sample msdf (RGB channels hold the signed distance field components)
    vec3 msdf = texture(textures[0], uv).rgb;

    // reconstruct signed distance in normalized [ -0.5..+0.5 ] units:
    float sd = median3(msdf.r, msdf.g, msdf.b) - 0.5;

    // convert to screen-space pixels (uPxRange = number of pixels represented by +0.5 -> -0.5)
    float pxDist = sd * uPxRange;

    // compute smoothing width using screen-space derivative of the distance in pixels
    // fwidth is abs(dFdx)+abs(dFdy) which is appropriate for anti-aliasing boundaries
    float afwidth = fwidth(pxDist);

    // final alpha using smoothstep; keeps edges crisp and scalable
    // if afwidth is tiny (very high-res), smoothstep still behaves correctly
    float alpha = smoothstep(-afwidth, afwidth, pxDist);

    // premultiply color by alpha (recommended) or output as usual depending on blending setup.
    // Here we assume standard blending: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    fragColor = vec4(uColor.rgb, uColor.a * alpha);

    // optional: discard tiny fragments for performance (uncomment if desired)
    //if (fragColor.a < 0.01) fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
