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

# Meta Quest tooling

This is a Meta Quest / Horizon OS sample. The bespoke intro above is the source of truth for what this project is and how it's built — use it (and the files it points at) instead of restating facts from memory.

When the user asks anything about Quest device behavior, build / deploy / debug / capture flows, on-device performance, or Horizon OS APIs, reach for these tools instead of generic Unreal answers:

- **`hzdb`** — Quest-aware ADB wrapper (device list, install / launch / stop, logs, screenshots, Perfetto traces, on-device docs search). Already wired up as an MCP server via `.mcp.json`, `.vscode/mcp.json`, and `.cursor/mcp.json`. Also runnable directly: `npx -y @meta-quest/hzdb <subcommand>`.
- **Meta Quest Agentic Tools** — the full skill set, including Unreal-specific skills: <https://github.com/meta-quest/agentic-tools>. Install per your client (Claude Code: `/plugin install meta-vr@meta-quest`; Gemini CLI: `gemini extensions install https://github.com/meta-quest/agentic-tools`; Cursor / VS Code: install the **Meta Horizon** extension from the Marketplace).

A few behavior expectations:

- **Read this repo's files first.** Before answering anything project-specific, read `README.md` and whichever source-of-truth files the intro above points at. Don't restate their contents in chat — quote or link instead.
- **Use `hzdb` for device-side work.** Anything that touches an attached Quest (install, launch, logs, screenshot, capture, manifest inspection) goes through `hzdb`, not raw `adb`.
- **Check live Horizon OS docs before answering API questions.** `hzdb docs search "..."` queries the live docs; training data on Horizon OS APIs goes stale fast.
- **Don't fabricate SDK / engine versions.** If a version isn't visible in this repo's files, say so rather than guessing.
