/*******************************************************************************
* hb_functions.c - Helper functions for Hungry Birds
* by Matthew Mongrain, 11-11-2015
*******************************************************************************/

#include "hb_functions.h"
#include <glib.h>
#include <stdlib.h>

void hb_destroy(gpointer data)
{
	free(data);
}
