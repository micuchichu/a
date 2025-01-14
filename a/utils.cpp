#include "utils.h"

void ImGuiStyleSetup()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.15f, 0.15f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.33f, 0.33f, 0.33f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.51f, 0.51f, 0.64f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.54f, 0.54f, 0.54f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.03f, 0.04f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.35f, 0.35f, 0.35f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.51f, 0.51f, 0.51f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.35f, 0.35f, 0.35f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.51f, 0.51f, 0.51f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.66f, 0.66f, 0.66f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.75f, 0.75f, 0.75f, 0.95f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.51f, 0.51f, 0.51f, 0.80f);
    colors[ImGuiCol_Tab] = ImVec4(0.35f, 0.35f, 0.35f, 0.86f);
    colors[ImGuiCol_TabSelected] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
    colors[ImGuiCol_TabDimmed] = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
    colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextLink] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    ImGui::GetStyle();
}

void fillDFS(int x, int y, char oldColor, char newColor, char tiles[sizeX][sizeY])
{
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY || tiles[y][x] != oldColor || tiles[y][x] == newColor)
		return;

	tiles[y][x] = newColor;

	fillDFS(x + 1, y, oldColor, newColor, tiles);
	fillDFS(x - 1, y, oldColor, newColor, tiles);
	fillDFS(x, y + 1, oldColor, newColor, tiles);
	fillDFS(x, y - 1, oldColor, newColor, tiles);
}

void UpdateTransform(Model& model, Vector3 pos)
{
	Matrix translation = MatrixTranslate(pos.x, pos.y, pos.z);
	Vector3 axis = Vector3Normalize({ 0, 0, 0 });
	float angle = 0;
	Matrix rotation = MatrixRotate(axis, angle);

	model.transform = MatrixMultiply(rotation, translation);
}

void addCubeVertices(Vector3* vertices, Color* colors, unsigned short* indices, int* vertexCount, int* indexCount, Vector2* texcoords, Vector3* normals, Vector3 pos, float width, float height, float depth, Color color)
{
    Vector3 cubeVertices[] = {
        { pos.x, pos.y, pos.z },
        { pos.x + width, pos.y, pos.z },
        { pos.x, pos.y + height, pos.z },
        { pos.x + width, pos.y + height, pos.z },
        { pos.x, pos.y, pos.z + depth },
        { pos.x + width, pos.y, pos.z + depth },
        { pos.x, pos.y + height, pos.z + depth },
        { pos.x + width, pos.y + height, pos.z + depth}
    };

    Vector3 cubeNormals[] = {
        { 0.0f, 0.0f, -1.0f },  // Front face
        { 1.0f, 0.0f, 0.0f },   // Right face
        { 0.0f, 0.0f, 1.0f },   // Back face
        { -1.0f, 0.0f, 0.0f },  // Left face
        { 0.0f, 1.0f, 0.0f },   // Top face
        { 0.0f, -1.0f, 0.0f }   // Bottom face
    };

    unsigned short cubeIndices[36] = {
        // Front face
        2, 1, 0, 2, 3, 1,
        // Right face
        7, 5, 1, 1, 3, 7,
        // Back face
        6, 4, 5, 5, 7, 6,
        // Left face
        2, 0, 4, 4, 6, 2,
        // Top face
        2, 6, 7, 7, 3, 2,
        // Bottom face
        0, 1, 5, 5, 4, 0
    };

    Vector2 cubeTexcoords[] = {
        { 0, height }, { width, height },
        { 0, 0 }, { width, 0 },
        { depth, height }, { height, width },
        { 0, depth }, { width, depth }
    };

    for (int i = 0; i < 8; i++)
    {
        vertices[*vertexCount] = cubeVertices[i];
        texcoords[*vertexCount] = cubeTexcoords[i];
        colors[*vertexCount] = color;
        normals[*vertexCount] = cubeNormals[i];
        (*vertexCount)++;
    }

    for (int i = 0; i < 36; i++) {
        indices[*indexCount] = cubeIndices[i] + (*vertexCount) - 8;
        (*indexCount)++;
    }
}

Model createSingleModel(char tiles[sizeY][sizeX], int floors, Vector3 pos)
{
	int maxVertices = sizeX * sizeY * floors * 8;
	int maxIndices = sizeX * sizeY * floors * 36;

	int visited[sizeY][sizeX] = { 0 };

	Vector3* vertices = (Vector3*)malloc(maxVertices * sizeof(Vector3));
	Color* colors = (Color*)malloc(maxVertices * sizeof(Color));
	unsigned short* indices = (unsigned short*)malloc(maxIndices * sizeof(unsigned short));
    Vector2* texcoords = (Vector2*)malloc(maxIndices * sizeof(Vector2));
    Vector3* normals = (Vector3*)malloc(maxVertices * sizeof(Vector3));

	int vertexCount = 0;
	int indexCount = 0;

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			char type = tiles[i][j];
			Color color;
			float height;
			Vector3 pos;

			switch (type)
			{
			case 0:
				color = RED;
				height = 4.0f * (floors - 1) + 1.0f;
				pos = { (float)j, 0, (float)i };

				addCubeVertices(vertices, colors, indices, &vertexCount, &indexCount, texcoords, normals, pos, 1.0f, height, 1.0f, color);
				continue;
			case 1:
				color = GREEN;
				height = 1.0f;
				break;
			case 2:
                color = BLUE;
				height = 0.5f;
				break;
			default:
				continue;
			}

			int width = 0, length = 0;

			if (tiles[i][j] > 0 && visited[i][j] == 0)
			{
				int value = tiles[i][j];

				for (int col = j; col < sizeX && tiles[i][col] == value && visited[i][col] == 0; col++)
					width++;

                for (int row = i; row < sizeY && tiles[row][j] == value && visited[row][j] == 0; row++)
                {
                    int col = j;
                    while (col < sizeX && tiles[row][col] == value && visited[row][col] == 0)
                        col++;

                    if (col - j != width)
                        break;
                    length++;
                }

				for (int x = i; x < i + length; x++)
                    for (int y = j; y < j + width; y++)
                    {
                        if (tiles[x][y] == value)
                            visited[x][y] = 1;
                    }

				for (int k = 0; k < floors; k++)
				{
					float yPos = k * 4.0f;
					if (type == 0 && k == floors - 1)
					{
						height = 1.0f;
					}

					pos = { (float)j, yPos, (float)i };

					addCubeVertices(vertices, colors, indices, &vertexCount, &indexCount, texcoords, normals, pos, width, height, length, color);
				}
			}
		}
	}

	Model model = LoadModelFromMesh({ 0 });

	model.meshCount = (vertexCount + 65520 - 1) / 65520;

	Vector3** splitVertices = (Vector3**)malloc(model.meshCount * sizeof(Vector3*));
	Color** splitColors = (Color**)malloc(model.meshCount * sizeof(Color*));
	unsigned short** splitIndices = (unsigned short**)malloc(model.meshCount * sizeof(unsigned short*));
    Vector3** splitNormals = (Vector3**)malloc(model.meshCount * sizeof(Vector3*));

	int* vertexCounts = (int*)malloc(model.meshCount * sizeof(int));
	int* indexCounts = (int*)malloc(model.meshCount * sizeof(int));
    Vector2** splitTexcoords = (Vector2**)malloc(model.meshCount * sizeof(Vector2*));

	int vertexOffset = 0, indexOffset = 0;

	for (int i = 0; i < model.meshCount; i++)
	{
		int currentVertexCount = (i == model.meshCount - 1) ? (vertexCount % 65520) : 65520;

		if (currentVertexCount == 0 && i == model.meshCount - 1)
			currentVertexCount = 65520;

		int currentIndexCount = 4.5 * currentVertexCount;

		splitVertices[i] = vertices + vertexOffset;
		splitIndices[i] = indices + indexOffset;
		splitColors[i] = colors + vertexOffset;
        splitTexcoords[i] = texcoords + indexOffset;
        splitNormals[i] = normals + vertexOffset;

		vertexCounts[i] = currentVertexCount;
		indexCounts[i] = currentIndexCount;

		vertexOffset += currentVertexCount + model.meshCount * 8;
		indexOffset += currentIndexCount + model.meshCount * 36;
	}

	Mesh* meshes = (Mesh*)malloc(model.meshCount * sizeof(Mesh));

    for (int i = 0; i < model.meshCount; i++)
    {
        Mesh mesh = { 0 };
		mesh.vertexCount = vertexCounts[i];
		mesh.triangleCount = indexCounts[i] / 3;

		mesh.vertices = (float*)splitVertices[i];

		mesh.indices = splitIndices[i];
		mesh.colors = (unsigned char*)splitColors[i];
        mesh.texcoords = (float*)splitTexcoords[i];
        mesh.normals = (float*)splitNormals[i];

		UploadMesh(&mesh, true);

		meshes[i] = mesh;
	}

	model.meshes = meshes;

	model.materialCount = 1;

	UpdateTransform(model, pos);
	free(vertices);
	free(splitVertices);
	free(vertexCounts);

	free(indices);
	free(splitIndices);
	free(indexCounts);

	free(colors);
	free(splitColors);

    free(normals);
    free(splitNormals);

	return model;
}

// ********** IMPORTANT NOTE **************
// 
// The functions below are taken from
// raylib's source code as i was too lazy
// to update the library
//

float CAMERA_MOVE_SPEED = 0.09f;

#define CAMERA_ROTATION_SPEED                           0.03f
#define CAMERA_PAN_SPEED                                0.2f

#define CAMERA_MOUSE_MOVE_SENSITIVITY                   0.002f

#define CAMERA_ORBITAL_SPEED                            0.5f

#define CAMERA_CULL_DISTANCE_NEAR      0.01
#define CAMERA_CULL_DISTANCE_FAR    1000.0

// Move Vector towards target
Vector3 Vector3MoveTowards(Vector3 v, Vector3 target, float maxDistance)
{
    Vector3 result = { 0 };

    float dx = target.x - v.x;
    float dy = target.y - v.y;
    float dz = target.z - v.z;
    float value = (dx * dx) + (dy * dy) + (dz * dz);

    if ((value == 0) || ((maxDistance >= 0) && (value <= maxDistance * maxDistance))) return target;

    float dist = sqrtf(value);

    result.x = v.x + dx / dist * maxDistance;
    result.y = v.y + dy / dist * maxDistance;
    result.z = v.z + dz / dist * maxDistance;

    return result;
}

Vector3 GetCameraForward(Camera* camera)
{
    return Vector3Normalize(Vector3Subtract(camera->target, camera->position));
}

Vector3 GetCameraUp(Camera* camera)
{
    return Vector3Normalize(camera->up);
}

Vector3 GetCameraRight(Camera* camera)
{
    Vector3 forward = GetCameraForward(camera);
    Vector3 up = GetCameraUp(camera);

    return Vector3Normalize(Vector3CrossProduct(forward, up));
}

void CameraMoveForward(Camera* camera, float distance, bool moveInWorldPlane)
{
    Vector3 forward = GetCameraForward(camera);

    if (moveInWorldPlane)
    {
        forward.y = 0;
        forward = Vector3Normalize(forward);
    }

    forward = Vector3Scale(forward, distance);

    camera->position = Vector3Add(camera->position, forward);
    camera->target = Vector3Add(camera->target, forward);
}

void CameraMoveUp(Camera* camera, float distance)
{
    Vector3 up = GetCameraUp(camera);

    up = Vector3Scale(up, distance);

    camera->position = Vector3Add(camera->position, up);
    camera->target = Vector3Add(camera->target, up);
}

void CameraMoveRight(Camera* camera, float distance, bool moveInWorldPlane)
{
    Vector3 right = GetCameraRight(camera);

    if (moveInWorldPlane)
    {
        right.y = 0;
        right = Vector3Normalize(right);
    }

    right = Vector3Scale(right, distance);

    camera->position = Vector3Add(camera->position, right);
    camera->target = Vector3Add(camera->target, right);
}

void CameraMoveToTarget(Camera* camera, float delta)
{
    float distance = Vector3Distance(camera->position, camera->target);

    distance += delta;

    if (distance <= 0) distance = 0.001f;

    Vector3 forward = GetCameraForward(camera);
    camera->position = Vector3Add(camera->target, Vector3Scale(forward, -distance));
}

void CameraYaw(Camera* camera, float angle, bool rotateAroundTarget)
{
    Vector3 up = GetCameraUp(camera);

    Vector3 targetPosition = Vector3Subtract(camera->target, camera->position);

    targetPosition = Vector3RotateByAxisAngle(targetPosition, up, angle);

    if (rotateAroundTarget)
    {
        camera->position = Vector3Subtract(camera->target, targetPosition);
    }
    else
    {
        camera->target = Vector3Add(camera->position, targetPosition);
    }
}

void CameraPitch(Camera* camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp)
{
    // Up direction
    Vector3 up = GetCameraUp(camera);

    // View vector
    Vector3 targetPosition = Vector3Subtract(camera->target, camera->position);

    if (lockView)
    {
        float maxAngleUp = Vector3Angle(up, targetPosition);
        maxAngleUp -= 0.001f;
        if (angle > maxAngleUp) angle = maxAngleUp;

        float maxAngleDown = Vector3Angle(Vector3Negate(up), targetPosition);
        maxAngleDown *= -1.0f;
        maxAngleDown += 0.001f;
        if (angle < maxAngleDown) angle = maxAngleDown;
    }

    Vector3 right = GetCameraRight(camera);

    targetPosition = Vector3RotateByAxisAngle(targetPosition, right, angle);

    if (rotateAroundTarget)
    {
        camera->position = Vector3Subtract(camera->target, targetPosition);
    }
    else
    {
        camera->target = Vector3Add(camera->position, targetPosition);
    }

    if (rotateUp)
    {
        camera->up = Vector3RotateByAxisAngle(camera->up, right, angle);
    }
}

Matrix GetCameraViewMatrix(Camera* camera)
{
    return MatrixLookAt(camera->position, camera->target, camera->up);
}

Matrix GetCameraProjectionMatrix(Camera* camera, float aspect)
{
    if (camera->projection == CAMERA_PERSPECTIVE)
    {
        return MatrixPerspective(camera->fovy * DEG2RAD, aspect, CAMERA_CULL_DISTANCE_NEAR, CAMERA_CULL_DISTANCE_FAR);
    }
    else if (camera->projection == CAMERA_ORTHOGRAPHIC)
    {
        double top = camera->fovy / 2.0;
        double right = top * aspect;

        return MatrixOrtho(-right, right, -top, top, CAMERA_CULL_DISTANCE_NEAR, CAMERA_CULL_DISTANCE_FAR);
    }

    return MatrixIdentity();
}

void UpdateCameraNew(Camera* camera, int mode)
{
    Vector2 mousePositionDelta = { 0 };
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        mousePositionDelta = GetMouseDelta();

    bool moveInWorldPlane = ((mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON));
    bool rotateAroundTarget = ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    bool lockView = ((mode == CAMERA_FREE) || (mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    bool rotateUp = false;

    if (mode == CAMERA_ORBITAL)
    {
        // Orbital can just orbit
        Matrix rotation = MatrixRotate(GetCameraUp(camera), CAMERA_ORBITAL_SPEED * GetFrameTime());
        Vector3 view = Vector3Subtract(camera->position, camera->target);
        view = Vector3Transform(view, rotation);
        camera->position = Vector3Add(camera->target, view);
        CameraMoveToTarget(camera, -GetMouseWheelMove());
    }
    else
    {
        if (IsKeyDown(KEY_DOWN)) CameraPitch(camera, -CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
        if (IsKeyDown(KEY_UP)) CameraPitch(camera, CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
        if (IsKeyDown(KEY_RIGHT)) CameraYaw(camera, -CAMERA_ROTATION_SPEED, rotateAroundTarget);
        if (IsKeyDown(KEY_LEFT)) CameraYaw(camera, CAMERA_ROTATION_SPEED, rotateAroundTarget);

        if ((mode == CAMERA_FREE) && (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)))
        {
            const Vector2 mouseDelta = GetMouseDelta();
            if (mouseDelta.x > 0.0f) CameraMoveRight(camera, CAMERA_PAN_SPEED, moveInWorldPlane);
            if (mouseDelta.x < 0.0f) CameraMoveRight(camera, -CAMERA_PAN_SPEED, moveInWorldPlane);
            if (mouseDelta.y > 0.0f) CameraMoveUp(camera, -CAMERA_PAN_SPEED);
            if (mouseDelta.y < 0.0f) CameraMoveUp(camera, CAMERA_PAN_SPEED);
        }
        else
        {
            CameraYaw(camera, -mousePositionDelta.x * CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
            CameraPitch(camera, -mousePositionDelta.y * CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);
        }

        if (IsKeyDown(KEY_W)) CameraMoveForward(camera, CAMERA_MOVE_SPEED, true);
        if (IsKeyDown(KEY_A)) CameraMoveRight(camera, -CAMERA_MOVE_SPEED, true);
        if (IsKeyDown(KEY_S)) CameraMoveForward(camera, -CAMERA_MOVE_SPEED, true);
        if (IsKeyDown(KEY_D)) CameraMoveRight(camera, CAMERA_MOVE_SPEED, true);

        if (mode == CAMERA_FREE)
        {
            if (IsKeyDown(KEY_SPACE)) CameraMoveUp(camera, CAMERA_MOVE_SPEED);
            if (IsKeyDown(KEY_LEFT_SHIFT)) CameraMoveUp(camera, -CAMERA_MOVE_SPEED);
            if (IsKeyPressed(KEY_LEFT_CONTROL)) CAMERA_MOVE_SPEED *= 2;
            if (IsKeyReleased(KEY_LEFT_CONTROL)) CAMERA_MOVE_SPEED /= 2;
        }
    }

    if (mode == CAMERA_FREE)
    {
        if (GetMouseWheelMove() > 0)
            CAMERA_MOVE_SPEED *= 1.1f;
        else if(GetMouseWheelMove() < 0)
            CAMERA_MOVE_SPEED /= 1.1f;
    }
}