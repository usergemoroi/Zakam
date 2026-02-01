bool defchams = false, chams = false, wire = false, glow = false, outline = false, skycolor = false, rainb = false, night = false;
float tX, tY, tZ;
float hX, hY, hZ;
float sx, sy, sz;
int rgb = 1;
bool rF = true, gF, bF = true, rF_, gF_, bF_;
float redd = 255.0f, greenn = 0.0f, bluee = 255.0f;
int glove;
int smode = 0;
bool gloveset = false, ragb = false;
ImVec4 cclr;
int linewidth = 150;
void perfRGBChange() {
    switch (rgb) {
        case 0: {
            if (gF) {
                greenn--; 
                if (!greenn) { gF = !gF;  rF_ = !rF_; }
            break; }
        if (redd < 255 && rF_) redd++;
        else { rgb++; redd = 255; rF = !rF; rF_ = !rF_; }
        break; } 
        case 1: {
            if (bF) {
                bluee--; 
                if (!bluee) { bF = !bF; gF_ = !gF_; }
            break; }
        if (greenn < 255 && gF_) greenn++;
        else { rgb++; greenn = 255; gF = !gF; gF_ = !gF_; }
        break; } case 2: {
        if (rF) {
            redd--; 
            if (!redd) { rF = !rF; bF_ = !bF_; }
        break; }
        if (bluee < 255 && bF_) bluee++;
        else { rgb = 0; bluee = 255; bF = !bF; bF_ = !bF_; }
        }
    }
	cclr.x = redd;
	cclr.y = greenn;
	cclr.z = bluee;
}

int (*old_glGetUniformLocation)(GLuint, const GLchar *);
GLint new_glGetUniformLocation(GLuint program, const GLchar *name) {
	//LOGI("Another One Shader Found : %s", name);
    return old_glGetUniformLocation(program, name);
}
void (*old_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void *indices);
void new_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    old_glDrawElements(mode, count, type, indices);
	GLint currProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
	GLint id = old_glGetUniformLocation(currProgram, oxorany("_BumpMap"));
	GLint id2 = old_glGetUniformLocation(currProgram, oxorany("_MainTex"));
	if (id2 != -1 && id == -1) {
		if (mode != GL_TRIANGLES || count < 1000) return;
	}
    if (mode != GL_TRIANGLES || count < 1500) return;
    {
        if (id == -1) return;
		if (rainb) {
			perfRGBChange();
			perfRGBChange();
		}
        if (chams) {
           glDepthRangef(1, 0.5);
           glEnable(GL_BLEND);
           glBlendFunc(GL_SRC_COLOR, GL_CONSTANT_COLOR);
           glBlendEquation(GL_FUNC_ADD);
           glBlendColor(cclr.x, cclr.y, cclr.z, 1.000);
           glDepthFunc(GL_ALWAYS);
           old_glDrawElements(GL_TRIANGLES, count, type, indices);
           glColorMask(cclr.x, cclr.y, cclr.z, 255);
           glBlendFunc(GL_DST_COLOR, GL_ONE);
           glDepthFunc(GL_LESS);
           glDepthMask(true);
           glDepthMask(false);
           glBlendColor(0.0, 0.0, 0.0, 0.0);
        }
        if (wire) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glEnable(GL_BLEND);
            glDepthFunc(GL_ALWAYS);
            glDepthMask(false);
            glBlendFunc(GL_CONSTANT_COLOR, GL_ZERO);
            glColorMask(cclr.x, cclr.y, cclr.z, 1.0f);
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(-2.5f, -2.5f);
            glLineWidth(linewidth);
            old_glDrawElements(GL_LINE_LOOP, count, type, indices);
            glDepthFunc(GL_LESS);
            glBlendFunc(GL_ONE, GL_ZERO);
            glColorMask(cclr.x, cclr.y, cclr.z, 0.8f);
            glDisable(GL_POLYGON_OFFSET_FILL);
        }
        if (glow) {
            glEnable(GL_BLEND);
            glLineWidth(linewidth);
            glDepthMask(true);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBlendColor(0.0, 0.0, 0.0, 0.1);
            glDepthFunc(0x0207);
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
            glColorMask(cclr.x, cclr.y, cclr.z, 255);
            glBlendFunc(GL_DST_COLOR, GL_ONE);
            glDepthFunc(0x0201);
            glDepthMask(true);
            glDepthMask(false);
            glBlendColor(0.0, 0.0, 0.0, 0.0);
            old_glDrawElements(GL_LINE_LOOP, count, type, indices);
        }
		if (outline) {
            glDepthRangef(1, 0);
            glLineWidth(linewidth);
            glEnable(GL_BLEND);
            glColorMask(1, 1, 1, 1);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            glBlendColor(0, 0, 0, 1);
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
            glBlendColor(GLfloat(cclr.x/100), GLfloat(cclr.y/100), GLfloat(cclr.z/100), 1);
            glDepthRangef(1, 0.5);
            glBlendColor(GLfloat(float(cclr.x)/255), GLfloat(float(cclr.y)/255), GLfloat(float(cclr.z)/255), 1);
            old_glDrawElements(GL_LINES, count, type, indices);
        }
        if (defchams) {
           glDepthRangef(1, 0.5);
           glColorMask(cclr.x, cclr.y, cclr.z, 1);
           glEnable(GL_BLEND);
           glBlendFunc(GL_SRC_ALPHA, GL_ONE);
           glBlendEquation(GL_FUNC_ADD);
           glBlendColor(cclr.x*3.92156863*0.001, cclr.y*3.92156863*0.001, cclr.z*3.92156863*0.001, 1.000);
        }
        old_glDrawElements(mode, count, type, indices);
        glDepthMask(true);
        glDepthFunc(GL_LESS);
        glDepthRangef(0.5, 1);
        glColorMask(1, 1, 1, 1);
        glDisable(GL_BLEND);
    }
}
