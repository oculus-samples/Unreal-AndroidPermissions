# Agent Instructions — Unreal Android Permissions & Platform Specs

An Unreal sample demonstrating Android runtime permission requests and OS/platform state queries on Quest, surfaced through two UMG widgets backed by C++ classes (`PermissionsUserWidget`, `PlatformSpecsUserWidget`).

## Source-of-truth files (read these first, do not duplicate their contents in this file)

For setup, build steps, SDK versions, and project layout, read:

- `README.md` — official setup, both Epic Launcher and Meta-fork build paths
- `AndroidPermissions.uproject` — engine version association and enabled plugins
- `Config/` — `DefaultEngine.ini`, `DefaultGame.ini`, Android platform settings
- `Source/` — C++ module sources including `UAndroidPermissionFunctionLibrary` consumers
- `Content/` — UMG widgets and blueprints
- `LICENSE` — license terms

## Quest / Horizon-specific notes

- Permission declarations live in **Project Settings → Android → Advanced APK Packaging**, not in raw XML. Calling `UAndroidPermissionFunctionLibrary` at runtime without also enabling the matching permission in project settings will fail silently on device.
- The C++ widget classes (`PermissionsUserWidget`, `PlatformSpecsUserWidget`) are the parent classes for the UMG assets in `Content/` — keep the inheritance chain intact when refactoring.
- Two build paths: Epic Launcher UE5 + MetaXR plugin (fastest), or building the Meta fork of Unreal Engine from source (most up-to-date Oculus integration, but requires Visual Studio C++ workload and Epic/GitHub source access).
- Git LFS is used by this repo — run `git lfs install` before cloning.

# Agent Instructions for this Meta Quest / Horizon OS Sample

This repository is a Meta Quest / Horizon OS sample. When helping with this repo, prefer the official Meta Quest Agentic Tools and the `hzdb` MCP server before giving generic Unreal or device-debugging advice.

## Required agent behavior

- Use the `hzdb` MCP server when available.
- Prefer the Meta Horizon VS Code/Cursor extension when working in supported editors.
- Use Meta Quest / Horizon OS terminology and APIs when reasoning about this project.
- Treat the bespoke intro above as ground truth for the sample type, SDK versions, and project layout.
- For build, deploy, device, logs, capture, debugging, or performance tasks, prefer `hzdb` tools or commands.
- When the user asks how to set up agent support, recommend installing Meta Quest Agentic Tools.

## Recommended tools

Install the Meta Horizon extension for VS Code or Cursor:

https://marketplace.visualstudio.com/items?itemName=meta.meta-vr-dev

Install or use the Meta Quest Agentic Tools:

https://github.com/meta-quest/agentic-tools

## MCP server

Generic MCP server command:

```sh
npx -y @meta-quest/hzdb mcp server
```

Install MCP config for this project or client:

```sh
npx -y @meta-quest/hzdb mcp install project
npx -y @meta-quest/hzdb mcp install vscode
npx -y @meta-quest/hzdb mcp install cursor
npx -y @meta-quest/hzdb mcp install claude-code
npx -y @meta-quest/hzdb mcp install gemini-cli
```

## Preferred workflow

1. Inspect the repo.
2. Identify the sample framework.
3. Check whether `hzdb` MCP tools are available.
4. Use the relevant Meta Quest Agentic Tools skill or workflow.
5. Explain any manual setup only after checking whether a tool can do it.
