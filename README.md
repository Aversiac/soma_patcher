Removes an error in the texture streaming/allocation system in which HPL3 can return a null/garbage ptr as result of lack of a guard in a few callsites. 
Without the patch, larger maps will hard-crash the game when you attempt to load into them after saving.
This patcher fixes that and also resolves a throttling bug in which many textures would load in at low resolution (sometimes not load in at all).
