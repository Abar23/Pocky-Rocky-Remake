


class Camera
{

	glm::mat4 getCamera() {
		glm::lookAt(Position, Position + Front, Up);
	}
	
}
