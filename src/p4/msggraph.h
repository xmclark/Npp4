/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * msggraph.h - definitions of graph depot specific errors
 */

class MsgGraph {

    public:

	static ErrorId CommitDataShort;
	static ErrorId UseGraph;
	static ErrorId UseCatFile;
	static ErrorId UseLsTree;
	static ErrorId UseDiffTree;
	static ErrorId UseLog;
	static ErrorId UseShowRef;
	static ErrorId UseMerge;
	static ErrorId UseRefHist;
	static ErrorId UseRevList;
	static ErrorId UseReceivePack;
	static ErrorId UsePackObjects;
	static ErrorId UseGraphDescribe;
	static ErrorId UseGraphSync;
	static ErrorId UseGraphProtects;
	static ErrorId UseGraphList;
	static ErrorId UseGraphCollect;
	static ErrorId UseGraphForkRepo;
	static ErrorId UseGraphDeleteRepo;
	static ErrorId UseGraphLFSPush;
	static ErrorId UseGraphLFSFetch;
	static ErrorId UseGraphLFSStat;
	static ErrorId UseGraphVerify;
	static ErrorId UsePermissionG;
	static ErrorId UsePermissionR;
	static ErrorId UsePermissionS;
	static ErrorId UsePermissionC;
	static ErrorId UsePubKey;
	static ErrorId UsePubKeyS;
	static ErrorId ReferenceData;
	static ErrorId ReferenceHistory;
	static ErrorId ReferenceDataShort;
	static ErrorId ReferenceHeadShort;
	static ErrorId ReferenceHaveShort;
	static ErrorId RepoDefaultBranch;
	static ErrorId FileLogData;
	static ErrorId RepositoryData;
	static ErrorId WrongClientType;
	static ErrorId CurrentBranchShort;
	static ErrorId NoSuchObject;
	static ErrorId NoSuchCommit;
	static ErrorId NoSuchDepot;
	static ErrorId PackRefSyntax;
	static ErrorId PackHeader;
	static ErrorId PackMagic;
	static ErrorId PackIndexCount;
	static ErrorId PackTypeByte;
	static ErrorId PackSizeByte;
	static ErrorId PackIdxFanoutRead;
	static ErrorId PackIdxEndOfFile;
	static ErrorId PackIdxPartial;
	static ErrorId PackOffsetEndOfFile;
	static ErrorId PackOffsetPartial;
	static ErrorId PackIdxLargeEndOfFile;
	static ErrorId PackLargeOffsetPartial;
	static ErrorId DeltaVarint;
	static ErrorId DeltaOffset;
	static ErrorId DeltaOffsetMore;
	static ErrorId DeltaOffsetBits;
	static ErrorId DeltaCopyOffset;
	static ErrorId DeltaLengthBits;
	static ErrorId DeltaCopyLength;
	static ErrorId DeltaRefBaseMissing;
	static ErrorId DeltaLengthMismatch;
	static ErrorId DeltaInsertData;
	static ErrorId CommitMissing;
	static ErrorId CommitNotUnique;
	static ErrorId TagMissing;
	static ErrorId TagNotUnique;
	static ErrorId NoEmailStart;
	static ErrorId NoEmailEnd;
	static ErrorId NoCommitDate;
	static ErrorId TreeModeEndOfFile;
	static ErrorId TreeNameEndOfFile;
	static ErrorId TreeShaEndOfFile;
	static ErrorId LbrShaSyntax;
	static ErrorId LbrWrongType;
	static ErrorId InvalidBlobHeader;
	static ErrorId LbrBadAccess;
	static ErrorId LbrPackBadAccess;
	static ErrorId LooseWriterBadAccess;
	static ErrorId LbrWriteOnly;
	static ErrorId TreeMissing;
	static ErrorId BlobMissing;
	static ErrorId LFSBlobMissing;
	static ErrorId TreeNotUnique;
	static ErrorId RcvRefSyntax;
	static ErrorId RcvFileName;
	static ErrorId NotFastForward;
	static ErrorId NotAGraphDepot;
	static ErrorId UnknownRepo;
	static ErrorId IllegalRefChar;
	static ErrorId IllegalRefSubstr;
	static ErrorId UnqualifiedRef;
	static ErrorId InvalidParentChar;
	static ErrorId NoSuchParent;
	static ErrorId RefTargetMissing;
	static ErrorId InvalidReference;
	static ErrorId InvalidRepo;
	static ErrorId PackObjectCount;
	static ErrorId PackObjectMissing;
	static ErrorId PackObjectLength;
	static ErrorId InvalidRepoName;
	static ErrorId NotASha256;
	static ErrorId LFSShaMismatch;
	static ErrorId LFSAlreadyPresent;
	static ErrorId AtomicPushFailed;
	static ErrorId TriggerWarnMessage;
	static ErrorId UseRepo;
	static ErrorId UseRepoo;
	static ErrorId UseRepoi;
	static ErrorId UseRepod;
	static ErrorId UseRepos;
	static ErrorId ReposData;
	static ErrorId RepoSave;
	static ErrorId RepoNoChange;
	static ErrorId RepoDelete;
	static ErrorId NoSuchRepo;
	static ErrorId BadRepoName;
	static ErrorId NotInGraphDepot;
	static ErrorId CantAutocreateRepo;
	static ErrorId MustForceFork;
	static ErrorId ShowPermission;
	static ErrorId DepotHasRepos;
	static ErrorId EmptyRepo;
	static ErrorId AmbiguousRepoName;
	static ErrorId AmbiguousRefUpdate;
	static ErrorId CantCreateRepo;
	static ErrorId CantWriteAllRepo;
	static ErrorId CantDeleteRepo;
	static ErrorId CantPruneRepo;
	static ErrorId CantChangeView;
	static ErrorId NoPermissionOnRef;
	static ErrorId RepoAccessDenied;
	static ErrorId NoMatchPermissions;
	static ErrorId NoLFSPushPerm;
	static ErrorId NoLFSFetchPerm;
	static ErrorId PubKeyData;
	static ErrorId BadPublicKey;
	static ErrorId PubKeyTooLong;
	static ErrorId PubKeyDuplicate;
	static ErrorId PubKeyAction;
	static ErrorId PubKeyNotExist;
	static ErrorId PubKeyNeedsForce;
	static ErrorId BlobVerified;
	static ErrorId BlobDamaged;
	static ErrorId LFSBlobVerified;
	static ErrorId LFSBlobDamaged;
	static ErrorId ArchiveImported;
	static ErrorId ReferenceAdded;
	static ErrorId ReferenceUpdated;
	static ErrorId ReferenceDeleted;
	static ErrorId ReferenceForced;
	static ErrorId ObjectStatistics;
	static ErrorId ForkTargetNotEmpty;
	static ErrorId ForkTargetIsSource;
	static ErrorId DanglingObject;
	static ErrorId NoRepoSelected;
	static ErrorId RefAlreadyExists;
	static ErrorId RefDoesntExist;
	static ErrorId RefValidation;
	static ErrorId SpecifyForce;

	// Retired ErrorIds. We need to keep these so that clients 
	// built with newer apis can commnunicate with older servers 
	// still sending these.
} ;
