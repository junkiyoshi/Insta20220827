#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int size = 30;

	for (int x = size * -10; x <= size * 10; x += size * 2) {

		for (int y = size * -10; y <= size * 10; y += size * 2) {

			if (x == 0 && y == 0) { continue; }

			auto location = glm::vec2(x, y);
			int distance = glm::length(location); 
			int deg = ofMap(ofNoise(distance * 0.003 - ofGetFrameNum() * 0.038), 0, 1, -120, 120);

			deg += std::atan2(location.y, location.x) * RAD_TO_DEG;

			auto next_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD)) + location;

			ofSetLineWidth(0.25);
			ofDrawCircle(location, size * 0.9);

			ofSetLineWidth(1);
			this->draw_arrow(location, next_location, size * 0.7);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 next_location, float size) {

	auto angle = std::atan2(next_location.y - location.y, next_location.x - location.x);

	ofSetColor(0);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.8 * cos(angle), size * 0.8 * sin(angle)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) + location);
	ofEndShape(true);

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape(true);

	ofSetColor(255);
	ofNoFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.8 * cos(angle), size * 0.8 * sin(angle)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}