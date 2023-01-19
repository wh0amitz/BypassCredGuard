## BypassCredGuard - Credential Guard Bypass Via Patching Wdigest Memory

### Background

Adam Chester ([@\_xpn\_](https://twitter.com/_xpn_)) wrote an article called "[Exploring Mimikatz - Part 1 - WDigest](https://blog.xpnsec.com/exploring-mimikatz-part-1/)" about memory patching to enable UseLogonCredential and make Wdigest cache cleartext credentials intrigued me.

The wdigest.dll module loaded by the LSASS process has two interesting global variables: `g_fParameter_useLogonCredential` and `g_IsCredGuardEnabled`, their role is self-evident from the name alone, the former is used to determine whether the clear text password should be stored in memory , the latter holds the state of the Windows Defender Credential Guard within the module, and Wdigest plaintext password caching can be enabled on systems with Credential Guard by patching the values of these two global variables in memory.

For a more detailed analysis, please read my blog: "[Revisiting a Credential Guard Bypass From Wdigest](https://whoamianony.top/revisiting-a-credential-guard-bypass-from-wdigest/)"

### Let’s see it in action

Run the POC we wrote on the system with Credential Guard protection enabled. When the user enters the username and password to log in again, we get his plaintext password again, as shown in the figure below.

```c++
BypassCredGuard.exe
```

![](/images/image-20230118230536164.png)

### As a reminder

In fact, as early as August 2020, Team Hydra ([@N4k3dTurtl3](https://twitter.com/N4k3dTurtl3)) published an article on the blog titled [《Bypassing Credential Guard》](https:// teamhydra.blog/2020/08/25/bypassing-credential-guard/) discusses this very clever and simple trick and briefly publishes a conceptual [CredGuard_PoC](https://gist.github .com/N4kedTurtle/8238f64d18932c7184faa2d0af2f1240), but it doesn't work on all Windows systems.

Team Hydra submitted a report to Microsoft about this issue and received the following response:

> "After investigating this issue, we do not believe this is a Credential Guard bypass. Credential Guard is meant to protect credentials that were cached while the feature is enabled. If a privileged user disables Credential Guard, then the feature cannot protect subsequent logons. We'll update our public documentation to clarify this behavior"

Given this response, I suspect this will be a reliable method of gaining clear text credentials on systems with Credential Guard enabled for the foreseeable future.
