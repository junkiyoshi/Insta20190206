#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color(39);
	int radius = 320;

	vector<glm::vec2> locations;
	for (int i = 1; i <= 5; i++) {

		float noise_seed = ofRandom(1000);
		for (int x = 0; x <= ofGetWidth(); x += 10) {

			float y = ofMap(ofNoise(noise_seed, x * 0.0015 * i, ofGetFrameNum() * 0.003), 0, 1, ofGetHeight() * 0.1, ofGetHeight() * 0.9);
			locations.push_back(glm::vec2(x, y));
		}
	}

	for (auto location : locations) {

		bool draw_circle = false;
		float draw_radius = 1;
		float circle_alpha = 0;
		for (auto other : locations) {

			if (location == other) { continue; }

			auto distance = glm::distance(location, other);
			if (distance < 25) {

				float alpha = ofMap(distance, 0, 25, 255, 128);
				ofSetColor(color, alpha);

				ofDrawLine(location, other);

				if (circle_alpha < alpha) { circle_alpha = alpha; }
				draw_circle = true;
				draw_radius += 1.5;
			}
		}

		if (draw_circle) {

			ofSetColor(color, circle_alpha);
			ofDrawCircle(location, draw_radius);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}