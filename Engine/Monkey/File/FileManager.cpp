#include "FileManager.h"
#include "Engine.h"

std::string FileManager::GetFilePath(const std::string& filepath)
{
	return Engine::Get()->GetAssetsPath() + "../../../examples/" + filepath;
}

bool FileManager::ReadFile(const std::string& filepath, uint8*& dataPtr, uint32& dataSize)
{
	std::string finalPath = FileManager::GetFilePath(filepath);

	FILE* file = fopen(finalPath.c_str(), "rb");
	if (!file)
	{
		MLOGE("File not found :%s", filepath.c_str());
		return false;
	}

	fseek(file, 0, SEEK_END);
	dataSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (dataSize <= 0)
	{
		fclose(file);
		MLOGE("File has no data :%s", filepath.c_str());
		return false;
	}

	dataPtr = new uint8[dataSize];
	fread(dataPtr, 1, dataSize, file);
	fclose(file);

	return true;
}