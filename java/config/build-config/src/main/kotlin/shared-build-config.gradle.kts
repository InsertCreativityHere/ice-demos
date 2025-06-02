// Copyright (c) ZeroC, Inc.

val runningInCi = providers.environmentVariable("CI").isPresent

plugins {
    // Apply the checkstyle plugin to find formatting violations.
    id("checkstyle")

    // Apply the rewrite plugin to find (and sometimes automatically fix) lint violations.
    id("org.openrewrite.rewrite")
}

checkstyle {
    toolVersion = "10.21.4"

    configDirectory.set(file("$rootDir/../../config/checkstyle/"))

    // If we're running in CI, we want the build to fail if any warnings are emitted.
    // This doesn't affect what checkstyle emits, just whether it 'fails' or 'succeeds' from Gradle's perspective.
    if (runningInCi) {
        maxWarnings = 0
    }
}
