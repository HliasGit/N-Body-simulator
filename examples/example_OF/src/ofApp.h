#pragma once

#include "ofMain.h"
#include "Parser.hpp"
#include "ofxBloom.h"
#include <vector>

class ofApp : public ofBaseApp
{
private:
	std::vector<std::vector<Vec>> particles_;
    std::vector<double> time_steps_;
	size_t iter_;

	ofEasyCam camera_;
	ofFbo fbo_;
	ofxBloom bloom_;
	size_t body_number;
	int scale_factor_;

public:
	void setup();
	void update();
	void draw();
	void ResetSimulation();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
