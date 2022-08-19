#pragma once

class ControllerInput {
public:

	float GetFloatValue(char* device);

};

ControllerInput& GetControllerInput();