#include "Map.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>

bool setMap(Map &map, uint8_t flags, uintptr_t address)
{
	Map cmp{};
	bool match = false;
	FILE *maps = fopen("/proc/self/maps", "rb");

	if (maps != nullptr)
	{
		while (!(feof(maps) || match))
		{
			fscanf(maps, "%p-%p %s %x %s %d%*[ ]%[^\n]", &cmp.start, &cmp.end, cmp.mode, &cmp.offset, cmp.dev, &cmp.inode, cmp.path);

			cmp.length = cmp.end - cmp.start;

			if (flags & MAP_START && map.start != cmp.start)
				continue;
			if (flags & MAP_END && map.end != cmp.end)
				continue;
			if (flags & MAP_MODE && strcmp(map.mode, cmp.mode) != 0)
				continue;
			if (flags & MAP_OFFSET && map.offset != cmp.offset)
				continue;
			if (flags & MAP_DEV && strcmp(map.dev, cmp.dev) != 0)
				continue;
			if (flags & MAP_INODE && map.inode != cmp.inode)
				continue;
			if (flags & MAP_PATH && !strstr(cmp.path, map.path))
				continue;
			if (flags & MAP_LENGTH && map.length != cmp.length)
				continue;
			if (address && (address < cmp.start || address > cmp.end))
				continue;

			memcpy(&map, &cmp, sizeof(Map));

			match = true;
		}

		fclose(maps);
	}

	return match;
}
