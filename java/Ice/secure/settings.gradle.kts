// Copyright (c) ZeroC, Inc.

pluginManagement {
    repositories {
        mavenLocal()
        maven("https://download.zeroc.com/nexus/repository/maven-nightly/")
        gradlePluginPortal() // Keep this to allow fetching other plugins
    }
}

rootProject.name = "secure"
include("client")
include("server")
