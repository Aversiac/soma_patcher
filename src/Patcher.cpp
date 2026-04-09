#include "CommonTypes.hpp"
#include "Constants.h"
#include <sstream>
#include <array>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct SiteConfig {
	const char* name;
	u64 site;
	u64 back;
	u64 full;
	size_t len;
};

struct ExpectedEntry {
	const char* name;
	const u8* data;
	std::size_t size;
};

struct PatchSet {
	const char* label;
	u64 cave_raw;
	u64 cave_va;
	const std::array<SiteConfig, 4>* sites;
	const std::array<ExpectedEntry, 4>* expected;
	const std::array<u8, 15>* prefix;
};

// =========================
// NoSteam patch data
// =========================

static const std::array<SiteConfig, 4> SITES_NOSTEAM = { {
	{ "func1_site1", 0x1402D54EEull, 0x1402D5500ull, 0x1402D56C6ull, 18 },
	{ "func1_site2", 0x1402D55BBull, 0x1402D55CAull, 0x1402D56C6ull, 15 },
	{ "func2_site1", 0x1402D59DEull, 0x1402D59F5ull, 0x1402D5BDAull, 23 },
	{ "func2_site2", 0x1402D5AB4ull, 0x1402D5AC3ull, 0x1402D5BDAull, 15 },
} };

static const std::array<u8, 18> EXPECTED_FUNC1_SITE1_NOSTEAM = {
	0x8B, 0xBB, 0x00, 0xC1, 0x02, 0x00, 0x33, 0xC0, 0x48, 0x8D, 0x55, 0xB0, 0x81, 0xE7, 0xFF, 0x07, 0x00, 0x00
};
static const std::array<u8, 15> EXPECTED_FUNC1_SITE2_NOSTEAM = {
	0x8B, 0xBB, 0x00, 0xC1, 0x02, 0x00, 0x41, 0xB6, 0x01, 0x81, 0xE7, 0xFF, 0x07, 0x00, 0x00
};
static const std::array<u8, 23> EXPECTED_FUNC2_SITE1_NOSTEAM = {
	0x8B, 0xB3, 0x00, 0xC1, 0x02, 0x00, 0x44, 0x8B, 0x8C, 0x24, 0xB0, 0x00, 0x00, 0x00, 0x45, 0x8B, 0xC6, 0x81, 0xE6, 0xFF, 0x07, 0x00, 0x00
};
static const std::array<u8, 15> EXPECTED_FUNC2_SITE2_NOSTEAM = {
	0x8B, 0xB3, 0x00, 0xC1, 0x02, 0x00, 0x41, 0xB5, 0x01, 0x81, 0xE6, 0xFF, 0x07, 0x00, 0x00
};

static const std::array<ExpectedEntry, 4> EXPECTED_NOSTEAM = { {
	{ "func1_site1", EXPECTED_FUNC1_SITE1_NOSTEAM.data(), EXPECTED_FUNC1_SITE1_NOSTEAM.size() },
	{ "func1_site2", EXPECTED_FUNC1_SITE2_NOSTEAM.data(), EXPECTED_FUNC1_SITE2_NOSTEAM.size() },
	{ "func2_site1", EXPECTED_FUNC2_SITE1_NOSTEAM.data(), EXPECTED_FUNC2_SITE1_NOSTEAM.size() },
	{ "func2_site2", EXPECTED_FUNC2_SITE2_NOSTEAM.data(), EXPECTED_FUNC2_SITE2_NOSTEAM.size() },
} };

static const std::array<u8, 15> PREFIX_NOSTEAM = {
	0x48, 0x8B, 0x83, 0x00, 0xC1, 0x02, 0x00,
	0x48, 0x2B, 0x83, 0x08, 0xC1, 0x02, 0x00,
};

// =========================
// Steam patch data
// =========================

static const std::array<SiteConfig, 4> SITES_STEAM = { {
	{ "func1_site1", 0x1402DDEAEull, 0x1402DDEC0ull, 0x1402DE086ull, 18 },
	{ "func1_site2", 0x1402DDF7Bull, 0x1402DDF8Aull, 0x1402DE086ull, 15 },
	{ "func2_site1", 0x1402DE39Eull, 0x1402DE3B5ull, 0x1402DE59Aull, 23 },
	{ "func2_site2", 0x1402DE474ull, 0x1402DE483ull, 0x1402DE59Aull, 15 },
} };

static const std::array<u8, 18> EXPECTED_FUNC1_SITE1_STEAM = {
	0x8B, 0xBB, 0x00, 0xC1, 0x02, 0x00, 0x33, 0xC0, 0x48, 0x8D, 0x55, 0xB0, 0x81, 0xE7, 0xFF, 0x07, 0x00, 0x00
};
static const std::array<u8, 15> EXPECTED_FUNC1_SITE2_STEAM = {
	0x8B, 0xBB, 0x00, 0xC1, 0x02, 0x00, 0x41, 0xB6, 0x01, 0x81, 0xE7, 0xFF, 0x07, 0x00, 0x00
};
static const std::array<u8, 23> EXPECTED_FUNC2_SITE1_STEAM = {
	0x8B, 0xB3, 0x00, 0xC1, 0x02, 0x00, 0x44, 0x8B, 0x8C, 0x24, 0xB0, 0x00, 0x00, 0x00, 0x45, 0x8B, 0xC6, 0x81, 0xE6, 0xFF, 0x07, 0x00, 0x00
};
static const std::array<u8, 15> EXPECTED_FUNC2_SITE2_STEAM = {
	0x8B, 0xB3, 0x00, 0xC1, 0x02, 0x00, 0x41, 0xB5, 0x01, 0x81, 0xE6, 0xFF, 0x07, 0x00, 0x00
};

static const std::array<ExpectedEntry, 4> EXPECTED_STEAM = { {
	{ "func1_site1", EXPECTED_FUNC1_SITE1_STEAM.data(), EXPECTED_FUNC1_SITE1_STEAM.size() },
	{ "func1_site2", EXPECTED_FUNC1_SITE2_STEAM.data(), EXPECTED_FUNC1_SITE2_STEAM.size() },
	{ "func2_site1", EXPECTED_FUNC2_SITE1_STEAM.data(), EXPECTED_FUNC2_SITE1_STEAM.size() },
	{ "func2_site2", EXPECTED_FUNC2_SITE2_STEAM.data(), EXPECTED_FUNC2_SITE2_STEAM.size() },
} };

static const std::array<u8, 15> PREFIX_STEAM = {
	0x48, 0x8B, 0x83, 0x00, 0xC1, 0x02, 0x00,
	0x48, 0x2B, 0x83, 0x08, 0xC1, 0x02, 0x00,
};

// =========================

static const PatchSet PATCH_NOSTEAM = {
	"NoSteam",
	0x6528B0ull,
	IMAGE_BASE + (0x6528B0ull - TEXT_RAW + TEXT_VA),
	&SITES_NOSTEAM,
	&EXPECTED_NOSTEAM,
	&PREFIX_NOSTEAM
};

static const PatchSet PATCH_STEAM = {
	"Steam",
	0x683CB0ull,
	IMAGE_BASE + (0x683CB0ull - TEXT_RAW + TEXT_VA),
	&SITES_STEAM,
	&EXPECTED_STEAM,
	&PREFIX_STEAM
};

struct TrampolineBlob {
	u64 va;
	std::vector<u8> code;
};

static const ExpectedEntry& get_expected(const PatchSet& patch, const std::string& name)
{
	for (const auto& e : *patch.expected)
	{
		if (name == e.name)
			return e;
	}
	throw std::runtime_error("Missing EXPECTED entry for " + name);
}

static u64 va_to_raw(u64 va)
{
	const u64 rva = va - IMAGE_BASE;
	return TEXT_RAW + (rva - TEXT_VA);
}

static std::array<u8, 4> rel32(u64 src_va_after, u64 dst_va)
{
	const i64 disp = static_cast<i64>(dst_va) - static_cast<i64>(src_va_after);
	if (disp < INT32_MIN || disp > INT32_MAX)
	{
		throw std::runtime_error("rel32 out of range");
	}

	const i32 d = static_cast<i32>(disp);
	return {
		static_cast<u8>((d >> 0) & 0xFF),
		static_cast<u8>((d >> 8) & 0xFF),
		static_cast<u8>((d >> 16) & 0xFF),
		static_cast<u8>((d >> 24) & 0xFF)
	};
}

static std::vector<u8> make_jmp(u64 from_va, u64 to_va)
{
	std::vector<u8> out;
	out.push_back(0xE9);
	const auto d = rel32(from_va + 5, to_va);
	out.insert(out.end(), d.begin(), d.end());
	return out;
}

static std::vector<u8> make_jae(u64 from_va, u64 to_va)
{
	std::vector<u8> out;
	out.push_back(0x0F);
	out.push_back(0x83);
	const auto d = rel32(from_va + 6, to_va);
	out.insert(out.end(), d.begin(), d.end());
	return out;
}

static u32 read_u32_le(const std::vector<u8>& data, std::size_t off)
{
	return static_cast<u32>(data.at(off + 0))
		| (static_cast<u32>(data.at(off + 1)) << 8)
		| (static_cast<u32>(data.at(off + 2)) << 16)
		| (static_cast<u32>(data.at(off + 3)) << 24);
}

static void write_u32_le(std::vector<u8>& data, std::size_t off, u32 value)
{
	data.at(off + 0) = static_cast<u8>((value >> 0) & 0xFF);
	data.at(off + 1) = static_cast<u8>((value >> 8) & 0xFF);
	data.at(off + 2) = static_cast<u8>((value >> 16) & 0xFF);
	data.at(off + 3) = static_cast<u8>((value >> 24) & 0xFF);
}

static void checksum_pe(std::vector<u8>& data)
{
	const u32 peoff = read_u32_le(data, 0x3C);
	const std::size_t checksum_off = static_cast<std::size_t>(peoff) + 24 + 64;

	write_u32_le(data, checksum_off, 0);

	u32 csum = 0;

	std::vector<u8> padded = data;
	if ((padded.size() & 1u) != 0u)
		padded.push_back(0);

	for (std::size_t i = 0; i < padded.size(); i += 2)
	{
		u16 word = 0;
		if (i != checksum_off && i != checksum_off + 2)
		{
			word = static_cast<u16>(padded[i])
				| (static_cast<u16>(padded[i + 1]) << 8);
		}

		csum = (csum + word) & 0xFFFFFFFFu;
		csum = (csum & 0xFFFFu) + (csum >> 16);
	}

	csum = (csum & 0xFFFFu) + (csum >> 16);
	csum = (csum + static_cast<u32>(data.size())) & 0xFFFFFFFFu;

	write_u32_le(data, checksum_off, csum);
}

static std::pair<std::vector<TrampolineBlob>, std::vector<u64>> build_trampolines(const PatchSet& patch)
{
	u64 cur_va = patch.cave_va;
	std::vector<TrampolineBlob> out;
	std::vector<u64> tramp_vas;

	auto emit = [&](const std::vector<u8>& code) -> u64
		{
			const u64 va = cur_va;
			out.push_back({ va, code });
			cur_va += static_cast<u64>(code.size());
			if ((cur_va % 8) != 0)
				cur_va += 8 - (cur_va % 8);
			return va;
		};

	auto mk = [&](const ExpectedEntry& original, u64 back_va, u64 full_va) -> u64
		{
			const u64 base = cur_va;
			std::vector<u8> code;

			code.insert(code.end(), patch.prefix->begin(), patch.prefix->end());

			const std::size_t jae_pos = code.size();
			code.push_back(0x0F);
			code.push_back(0x83);
			code.insert(code.end(), 4, 0x00);

			code.insert(code.end(), original.data, original.data + original.size);

			const std::size_t back_pos = code.size();
			code.push_back(0xE9);
			code.insert(code.end(), 4, 0x00);

			const std::size_t full_off = code.size();
			const u64 full_branch_va = base + static_cast<u64>(full_off);
			code.push_back(0xE9);
			code.insert(code.end(), 4, 0x00);

			const auto jae_bytes = make_jae(base + jae_pos, full_branch_va);
			std::memcpy(code.data() + jae_pos, jae_bytes.data(), jae_bytes.size());

			const auto back_bytes = make_jmp(base + back_pos, back_va);
			std::memcpy(code.data() + back_pos, back_bytes.data(), back_bytes.size());

			const auto full_bytes = make_jmp(full_branch_va, full_va);
			std::memcpy(code.data() + full_off, full_bytes.data(), full_bytes.size());

			return emit(code);
		};

	tramp_vas.push_back(mk(get_expected(patch, "func1_site1"), (*patch.sites)[0].back, (*patch.sites)[0].full));
	tramp_vas.push_back(mk(get_expected(patch, "func1_site2"), (*patch.sites)[1].back, (*patch.sites)[1].full));
	tramp_vas.push_back(mk(get_expected(patch, "func2_site1"), (*patch.sites)[2].back, (*patch.sites)[2].full));
	tramp_vas.push_back(mk(get_expected(patch, "func2_site2"), (*patch.sites)[3].back, (*patch.sites)[3].full));

	if (cur_va > patch.cave_va + 0x150)
		throw std::runtime_error("Not enough .text slack for trampolines");

	return { out, tramp_vas };
}

static std::vector<u8> read_all_bytes(const std::string& path)
{
	std::ifstream file(path, std::ios::binary);
	if (!file)
		throw std::runtime_error("Failed to open input file: " + path);

	file.seekg(0, std::ios::end);
	const std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	if (size < 0)
		throw std::runtime_error("Failed to determine file size");

	std::vector<u8> data(static_cast<std::size_t>(size));
	if (!file.read(reinterpret_cast<char*>(data.data()), size))
		throw std::runtime_error("Failed to read input file");

	return data;
}

static void write_all_bytes(const std::string& path, const std::vector<u8>& data)
{
	std::ofstream file(path, std::ios::binary);
	if (!file)
		throw std::runtime_error("Failed to open output file: " + path);

	file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
	if (!file)
		throw std::runtime_error("Failed to write output file");
}

static void patch_file(const PatchSet& patch, const std::string& src_path, const std::string& dst_path)
{
	std::vector<u8> data = read_all_bytes(src_path);

	for (const auto& cfg : *patch.sites)
	{
		const auto& expected = get_expected(patch, cfg.name);
		const std::size_t ro = static_cast<std::size_t>(va_to_raw(cfg.site));

		if (ro + cfg.len > data.size())
			throw std::runtime_error(std::string("Patch site out of range: ") + cfg.name);

		if (expected.size != cfg.len)
			throw std::runtime_error(std::string("Expected size mismatch for: ") + cfg.name);

		if (std::memcmp(data.data() + ro, expected.data, cfg.len) != 0)
		{
			std::ostringstream oss;
			oss << "[" << patch.label << "] Unexpected bytes at " << cfg.name << " 0x" << std::hex << cfg.site;
			throw std::runtime_error(oss.str());
		}
	}

	const auto [tramps, tramp_vas] = build_trampolines(patch);

	for (const auto& tramp : tramps)
	{
		const std::size_t ro = static_cast<std::size_t>(va_to_raw(tramp.va));
		if (ro + tramp.code.size() > data.size())
			throw std::runtime_error("Trampoline write out of range");

		std::memcpy(data.data() + ro, tramp.code.data(), tramp.code.size());
	}

	for (std::size_t i = 0; i < patch.sites->size(); ++i)
	{
		const auto& site_cfg = (*patch.sites)[i];
		const u64 tramp_va = tramp_vas[i];
		const std::size_t ro = static_cast<std::size_t>(va_to_raw(site_cfg.site));

		std::vector<u8> patch_bytes = make_jmp(site_cfg.site, tramp_va);
		patch_bytes.insert(patch_bytes.end(), site_cfg.len - 5, 0x90);

		if (ro + patch_bytes.size() > data.size())
			throw std::runtime_error("Site patch out of range");

		std::memcpy(data.data() + ro, patch_bytes.data(), patch_bytes.size());
	}

	checksum_pe(data);
	write_all_bytes(dst_path, data);
}

int main(int argc, char* argv[]) 
{
	try
	{
		std::cout << "Welcome to the SOMA Patcher!\n";
		std::cout << "This program modifies the game's .exe files (Soma.exe/Soma_NoSteam.exe) to fix:\n";
		std::cout << "- Crashes when loading saves on large maps\n";
		std::cout << "- Texture streaming issues (broken or low resolution textures)\n";
		std::cout << "For full documentation/source code, see the GitHub repository: https://github.com/Aversiac/soma_patcher \n";
		std::cout << "Press [ENTER] to continue... \n";
	//	std::cout << "Apply patches? Input one of the following... Y (Yes) // N (No)\n";
		// the patch is mandatory, should we really allow people to break their installs with a single keystroke?

		std::string input;
		std::getline(std::cin, input);

		//if (input == "y" || input == "Y")
		{
			patch_file(PATCH_NOSTEAM, "Soma_NoSteam.exe", "Soma_NoSteam.exe");
			patch_file(PATCH_STEAM, "Soma.exe", "Soma.exe");
		}

		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << "\n";
		std::cin.get();
		return 2;
	}
}
