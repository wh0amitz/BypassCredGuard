## BypassCredGuard - Credential Guard Bypass Via Patching Wdigest Memory

### Background

Adam Chester ([@_xpn_](https://twitter.com/_xpn_)) wrote an article called ["Exploring Mimikatz - Part 1 - WDigest"](https://blog.xpnsec.com/exploring- mimikatz-part-1/) about memory patching to enable UseLogonCredential and make Wdigest cache cleartext credentials intrigued me.

The wdigest.dll module loaded by the LSASS process has two interesting global variables: `g_fParameter_useLogonCredential` and `g_IsCredGuardEnabled`, their role is self-evident from the name alone, the former is used to determine whether the clear text password should be stored in memory , the latter holds the state of the Windows Defender Credential Guard within the module, and Wdigest plaintext password caching can be enabled on systems with Credential Guard by patching the values of these two global variables in memory.

### Let’s see it in action

Run the POC we wrote on the system with Credential Guard protection enabled. When the user enters the username and password to log in again, we get his plaintext password again, as shown in the figure below.

```c++
BypassCredGuard.exe
```

![](/images/image-20230118230536164.png)