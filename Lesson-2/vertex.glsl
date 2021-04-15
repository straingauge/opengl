#version 310 es


in vec3 pos;
out vec4 color;

void main() {
   gl_Position.xyz=pos;
   gl_Position.w=1.0;
   color=vec4(0.8,0.8,0.8,1.0);
}
