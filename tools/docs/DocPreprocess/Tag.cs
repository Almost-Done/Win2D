﻿// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Licensed under the MIT License. See LICENSE.txt in the project root for license information.

namespace DocPreprocess
{
    class Tag
    {
        public static readonly Tag[] Tags =
        {
            new Tag("Experimental", "This API is marked as [Experimental], meaning it may be subject to change in future Win2D releases.") { PropagateTypeTagsToMembers = true },
            new Tag("Win10", "This API is available on Windows 10 (Universal Windows Platform) only. It is not supported on Windows 8.1 or Phone 8.1."),
            new Tag("Win10_10586", "This API is only available when running on Windows 10 build 10586 or greater (released November 2015).") { PropagateTypeTagsToMembers = true },
            // TODO: replace 14346 with final RS1 SDK version (once known)
            new Tag("Win10_14346", "This API is only available when running on Windows 10 build 14346 or greater (released TODO 2016).") { PropagateTypeTagsToMembers = true },
            new Tag("NoComposition", "Supported by Win2D but not Windows.UI.Composition."),
        };


        public string Attribute { get; private set; }
        public string Description { get; private set; }

        public bool PropagateTypeTagsToMembers { get; private set; }


        public string Summary
        {
            get { return '[' + Attribute + ']'; }
        }


        Tag(string attribute, string description)
        {
            this.Attribute = attribute;
            this.Description = description;
        }
    }
}
