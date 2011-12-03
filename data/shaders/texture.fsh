uniform sampler2D colorTexture;

void main()
{
    gl_FragColor = texture2D(colorTexture, gl_TexCoord[0].st).bgra;
}
