/*
 * Glowing Spider Robot  –  C++ / OpenGL + GLUT
 *
 * Compile (Linux / macOS):
 *   g++ -O2 -o spider_robot spider_robot.cpp -lGL -lGLU -lglut -lm
 *
 * Compile (Windows with freeglut):
 *   g++ -O2 -o spider_robot spider_robot.cpp -lfreeglut -lopengl32 -lglu32 -lm
 *
 * Press ESC to quit.
 */
 
#ifdef _WIN32
#  include <windows.h>
#endif
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
 
// ── Globals ──────────────────────────────────────────────────────────────────
static float g_time = 0.0f;
static int   g_W    = 900;
static int   g_H    = 600;
 
// ── Utility ──────────────────────────────────────────────────────────────────
static float pulse()  { return 0.5f + 0.5f * sinf(g_time * 3.0f); }
static float deg2rad(float d) { return d * 3.14159265f / 180.0f; }
 
// Draw a filled 2-D circle (z = 0)
static void circle2D(float x, float y, float r, int segs = 40)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segs; ++i) {
        float a = 2.0f * 3.14159265f * i / segs;
        glVertex2f(x + r * cosf(a), y + r * sinf(a));
    }
    glEnd();
}
 
// Draw a thick line by rendering a thin quad
static void thickLine(float x0, float y0, float x1, float y1, float w)
{
    float dx = x1 - x0, dy = y1 - y0;
    float len = sqrtf(dx*dx + dy*dy);
    if (len < 0.001f) return;
    float nx = -dy / len * w * 0.5f;
    float ny =  dx / len * w * 0.5f;
    glBegin(GL_QUADS);
    glVertex2f(x0 + nx, y0 + ny);
    glVertex2f(x0 - nx, y0 - ny);
    glVertex2f(x1 - nx, y1 - ny);
    glVertex2f(x1 + nx, y1 + ny);
    glEnd();
}
 
// Soft radial glow (additive alpha layers)
static void glow2D(float x, float y, float r, float rr, float gg, float bb, int steps = 7)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);   // additive blending → glow!
    for (int i = steps; i >= 1; --i) {
        float frac  = (float)i / steps;
        float alpha = 0.18f * (1.0f - frac);
        glColor4f(rr, gg, bb, alpha);
        circle2D(x, y, r * frac);
    }
    glDisable(GL_BLEND);
}
 
// Ellipse outline
static void ellipseOutline(float cx, float cy, float rx, float ry,
                            float lw, int segs = 60)
{
    // use thick‐quad pairs
    for (int i = 0; i < segs; ++i) {
        float a0 = 2.0f * 3.14159265f * i       / segs;
        float a1 = 2.0f * 3.14159265f * (i + 1) / segs;
        float x0 = cx + rx * cosf(a0), y0 = cy + ry * sinf(a0);
        float x1 = cx + rx * cosf(a1), y1 = cy + ry * sinf(a1);
        thickLine(x0, y0, x1, y1, lw);
    }
}
 
// Filled ellipse
static void ellipseFill(float cx, float cy, float rx, float ry, int segs = 60)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segs; ++i) {
        float a = 2.0f * 3.14159265f * i / segs;
        glVertex2f(cx + rx * cosf(a), cy + ry * sinf(a));
    }
    glEnd();
}
 
// ── Scene ────────────────────────────────────────────────────────────────────
static void drawScene()
{
    float p  = pulse();
    float cx = g_W * 0.5f;
    float cy = g_H * 0.5f + 20.0f;
 
    // ── Background ────────────────────────────────────────────────────────
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
 
    // ── Floor glow (elliptical) ───────────────────────────────────────────
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (int r = 10; r >= 1; --r) {
        float frac  = (float)r / 10.0f;
        float alpha = 0.06f * frac * (0.7f + 0.3f * p);
        glColor4f(0.7f, 0.15f, 0.0f, alpha);
        ellipseFill(cx, cy + 65, 200 * frac, 50 * frac);
    }
    glDisable(GL_BLEND);
 
    // ── Flower shadow on floor ────────────────────────────────────────────
    for (int i = 0; i < 5; ++i) {
        float angle = 2.0f * 3.14159265f * i / 5 + g_time * 0.3f;
        float px = cx + 55 * cosf(angle);
        float py = cy + 90 + 18 * sinf(angle);
        glow2D(px, py, 30 + 4 * p, 0.7f * p, 0.2f * p, 0.0f, 5);
    }
 
    // ── Legs ──────────────────────────────────────────────────────────────
    struct LegCfg { float sdx, sdy, mdx, mdy, tdx, tdy; };
    LegCfg legs[8] = {
        {-110,-30, -190,-10, -260,  40},
        {-100, 10, -180, 50, -240, 110},
        { -90, 40, -170, 90, -210, 150},
        { -70, 55, -130,110, -150, 170},
        { 110,-30,  190,-10,  260,  40},
        { 100, 10,  180, 50,  240, 110},
        {  90, 40,  170, 90,  210, 150},
        {  70, 55,  130,110,  150, 170},
    };
 
    for (int idx = 0; idx < 8; ++idx) {
        float bob = 5.0f * sinf(g_time * 4.0f + idx * 0.8f);
        float sx = cx + legs[idx].sdx, sy = cy + legs[idx].sdy;
        float mx = cx + legs[idx].mdx, my = cy + legs[idx].mdy + bob;
        float tx = cx + legs[idx].tdx, ty = cy + legs[idx].tdy + bob * 0.5f;
 
        // Soft glow on joint points
        glow2D(mx, my, 14, 0.8f, 0.1f, 0.0f, 4);
 
        // Dark outer leg
        glColor3f(0.6f, 0.05f, 0.0f);
        thickLine(sx, sy, mx, my, 5);
        thickLine(mx, my, tx, ty, 5);
 
        // Bright inner highlight
        glColor3f(1.0f, 0.35f, 0.0f);
        thickLine(sx, sy, mx, my, 2);
        thickLine(mx, my, tx, ty, 2);
 
        // Joint nodes
        glColor3f(1.0f, 0.55f, 0.0f);
        circle2D(mx, my, 5);
        circle2D(sx, sy, 4);
    }
 
    // ── Body glow ─────────────────────────────────────────────────────────
    glow2D(cx, cy, 100, 0.8f, 0.1f, 0.0f, 10);
 
    // Body shell fill
    glColor3f(0.30f, 0.02f, 0.0f);
    ellipseFill(cx, cy, 70, 45);
 
    // Body shell outline
    glColor3f(0.8f, 0.12f, 0.0f);
    ellipseOutline(cx, cy, 70, 45, 3);
 
    // Carapace ridge arcs
    glColor3f(1.0f, 0.35f, 0.0f);
    for (int off = -1; off <= 1; ++off) {
        float ox = (float)(off * 10);
        for (int i = 0; i < 30; ++i) {
            float a0 = 3.14159265f * i       / 30;
            float a1 = 3.14159265f * (i + 1) / 30;
            float x0 = cx + ox + 55 * cosf(a0), y0 = cy - 25 + 20 * sinf(a0);
            float x1 = cx + ox + 55 * cosf(a1), y1 = cy - 25 + 20 * sinf(a1);
            thickLine(x0, y0, x1, y1, 1.5f);
        }
    }
 
    // ── Eyes ──────────────────────────────────────────────────────────────
    float eyeOffsets[2] = {-22, 22};
    for (int e = 0; e < 2; ++e) {
        float ex = cx + eyeOffsets[e], ey = cy - 10;
        glow2D(ex, ey, 28 + 6 * p, 1.0f, 0.35f, 0.0f, 7);
        // Iris
        glColor3f(0.8f + 0.2f * p, 0.08f, 0.0f);
        circle2D(ex, ey, 11);
        // Pupil glow
        glColor3f(1.0f, 0.55f, 0.0f);
        circle2D(ex, ey, 6);
        // Specular
        glColor3f(1.0f, 1.0f, 1.0f);
        circle2D(ex - 3, ey - 3, 2.5f);
    }
 
    // ── Under-belly light ─────────────────────────────────────────────────
    float br = 22 + 5 * p;
    glow2D(cx, cy + 30, br + 15, 1.0f, 0.55f, 0.0f, 6);
    glColor3f(1.0f, 0.55f, 0.0f);
    circle2D(cx, cy + 30, br);
    glColor3f(1.0f, 1.0f, 0.9f);
    circle2D(cx, cy + 30, br * 0.5f);
}
 
// ── GLUT callbacks ────────────────────────────────────────────────────────────
static void display()
{
    drawScene();
    glutSwapBuffers();
}
 
static void timer(int)
{
    g_time += 1.0f / 60.0f;
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}
 
static void keyboard(unsigned char key, int, int)
{
    if (key == 27) { exit(0); }   // ESC
}
 
static void reshape(int w, int h)
{
    g_W = w; g_H = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);   // y down to match typical 2D coords
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
// ── Entry point ───────────────────────────────────────────────────────────────
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(g_W, g_H);
    glutCreateWindow("Glowing Spider Robot");
 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
 
    glutMainLoop();
    return 0;
}