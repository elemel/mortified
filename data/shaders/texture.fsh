uniform sampler2D colorTexture;

void main()
{
    gl_FragColor = gl_TexCoord[1].s * gl_Color * texture2D(colorTexture, gl_TexCoord[0].st);
}
