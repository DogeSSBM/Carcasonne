#pragma once

#define TILE_TOTAL	72
#define TILE_VARIANTS	24

const Tile tileVarients[TILE_VARIANTS] = {
// 4 section
	{
		true,
		{false, false, false, false},
		{L_CITY, L_CITY, L_CITY, L_CITY, L_NONE},
	},{
		true,
		{false, false, false, false},
		{L_CITY, L_FIELD, L_FIELD, L_CITY, L_NONE},
	},{
		false,
		{false, true, true, false},
		{L_CITY, L_FIELD, L_FIELD, L_CITY, L_NONE},
	},{
		true,
		{false, true, true, false},
		{L_CITY, L_FIELD, L_FIELD, L_CITY, L_NONE},
	},{
		false,
		{false, false, false, false},
		{L_CITY, L_FIELD, L_FIELD, L_CITY, L_NONE},
	},{
		false,
		{true, false, true, false},
		{L_FIELD, L_FIELD, L_FIELD, L_FIELD, L_NONE},
	},{
		false,
		{false, false, true, true},
		{L_FIELD, L_FIELD, L_FIELD, L_FIELD, L_NONE},
	},{
		false,
		{false, true, true, true},
		{L_FIELD, L_FIELD, L_FIELD, L_FIELD, L_NONE},
	},{
		false,
		{true, true, true, true},
		{L_FIELD, L_FIELD, L_FIELD, L_FIELD, L_NONE},
	},
// 5 section 1
	{
		false,
		{false, false, false, false},
		{L_FIELD, L_FIELD, L_FIELD, L_FIELD, L_CHURCH},
	},{
		false,
		{false, false, true, false},
		{L_FIELD, L_FIELD, L_FIELD, L_FIELD, L_CHURCH},
	},{
		false,
		{false, false, false, false},
		{L_FIELD, L_CITY, L_FIELD, L_CITY, L_CITY},
	},{
		true,
		{false, false, false, false},
		{L_FIELD, L_CITY, L_FIELD, L_CITY, L_CITY},
	},{
		false,
		{false, false, false, false},
		{L_CITY, L_FIELD, L_FIELD, L_CITY, L_FIELD},
	},{
		false,
		{false, false, false, false},
		{L_CITY, L_FIELD, L_CITY, L_FIELD, L_FIELD},
	},{
		false,
		{false, true, true, true},
		{L_CITY, L_FIELD, L_FIELD, L_FIELD, L_FIELD},
	},
// 5 section 2
	{
		false,
		{false, true, false, true},
		{L_CITY, L_FIELD, L_FIELD, L_FIELD, L_FIELD},
	},{
		false,
		{false, false, false, false},
		{L_CITY, L_CITY, L_FIELD, L_CITY, L_CITY},
	},{
		true,
		{false, false, false, false},
		{L_CITY, L_CITY, L_FIELD, L_CITY, L_CITY},
	},{
		false,
		{false, false, true, false},
		{L_CITY, L_CITY, L_FIELD, L_CITY, L_CITY},
	},{
		true,
		{false, false, true, false},
		{L_CITY, L_CITY, L_FIELD, L_CITY, L_CITY},
	},{
		false,
		{false, false, false, false},
		{L_CITY, L_FIELD, L_FIELD, L_FIELD, L_FIELD},
	},{
		false,
		{false, false, true, true},
		{L_CITY, L_FIELD, L_FIELD, L_FIELD, L_FIELD},
	},{
		false,
		{false, true, true, false},
		{L_CITY, L_FIELD, L_FIELD, L_FIELD, L_FIELD},
	}
};

uint tileVarientNum[TILE_VARIANTS] = {
	1, 2, 3, 2, 3, 8, 9, 4, 1,
	4, 2, 1, 2, 2, 3, 3, 4, 3, 1, 1, 3, 5, 3, 3
};

uint deckSize = TILE_TOTAL;
Tile deck[TILE_TOTAL] = {0};
