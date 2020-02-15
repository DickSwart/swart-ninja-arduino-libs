# swart-ninja-rsw

## Breaking Changes
### 1.2.0
Constructor changed, allowing the option for a forced triger on first loop. This change will break your code if you specified a pin input type. To get the same result as in version 1.0 just specify a true value before the pin input type.

**Change this:**
```c++
SwartNinjaRSW lightSwitch(LIGHT_SWITCH_PIN, handleSwartNinjaSensorUpdate, INPUT);
```
**To this:**
```c++
SwartNinjaRSW lightSwitch(LIGHT_SWITCH_PIN, handleSwartNinjaSensorUpdate, true, INPUT);
```

---