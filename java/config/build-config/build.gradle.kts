
// Create a "convention plugin" that can be pulled in by the demos with Gradle's Kotlin DSL.

plugins {
    // Apply the Kotlin-DSL plugin development plugin.
    `kotlin-dsl`
}

repositories {
    mavenCentral()
    gradlePluginPortal()
}

dependencies {
    // Needed to pull in a specific version of the 'openrewrite' plugin.
    implementation("org.openrewrite.rewrite:org.openrewrite.rewrite.gradle.plugin:7.7.0")
}
