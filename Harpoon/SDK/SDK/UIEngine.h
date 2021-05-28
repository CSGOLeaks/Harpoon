//Menu UI Root - "CSGOMainMenu"
//In-Game UI Root - "CSGOHud"
#pragma once
#include <cstdint>
#include <array>
class IUIPanel;
class IUIEvent;
class IUIEngineFrameListener;
class IUIPanelStyle;
class IUIJSObject;
class IUIWindow;
class IUISettings;
class IUITextLayout;
class IUIInputEngine;
class IUILocalize;
class IUISoundSystem;
class IUISettings;
class IUILayoutManager;
class IUIFileSystem;
class IUIPanelClient;

// E Prefix for enums?
class EFontStyle;
class EFontWeight;
class ETextAlign;
class EPanelRepaint;
class EStyleRepaint;
class EStyleFlags;
class EFocusMoveDirection;
class EMouseCanActivate;
class EAnimationTimingFunction;
class EAnimationDirection;

class CUILength;
class CLayoutFile;
typedef unsigned short CPanoramaSymbol;
class PanelHandle_t;
class CJSONWebAPIParams;
class UIEventFactory;
class EPanelEventSource_t;
class CPanel2DFactory;
class RegisterJSType_t;
class RegisterJSScopeInfo_t;
class RegisterJSEntryInfo_t;
// Returned by the CreatePanel functions. TODO: Look at panelRefs this might be that.
class PanelWrapper {
public:
    void* vtable;
    IUIPanel* panel;
};


struct ScrollBehavior_t;

struct PanelArraySlot
{
    IUIPanel* panel;
    void* unk1;
    void* unk2;
    uint32_t someSymbol; // Might be a CPanoramaSymbol
    uint32_t boolean; // Looks to normally be 1, maybe IsVisible or IsFinishedSettingUp
};
struct PanelArray
{
    void* _pad; // all F's
    uint32_t size; // I don't think this is right.
    uint32_t unk;
    //TODO: This array is not fixed-size! Something like: CUtlVector
    //Make sure to check panel pointer when using this!
    std::array<PanelArraySlot, 1024> slots;
};
// "CUIPanel::RemoveAndDeleteChildren" XREF to Function
class IUIPanel
{
public:
    virtual void DESTROY1(void) = 0;
    virtual void DESTROY2(void) = 0;
    virtual void Initialize(IUIWindow*, IUIPanel*, const char*, unsigned int) = 0;
    virtual void InitClonedPanel(IUIPanel* other) = 0;
    virtual void RegisterEventHandlersOnPanel2DType(CPanoramaSymbol) = 0;
    virtual void Shutdown(void) = 0;
    virtual void FirePanelLoadedEvent(void) = 0;
    virtual void SetClientPtr(IUIPanelClient*) = 0;
    virtual IUIPanelClient* ClientPtr() = 0;
    virtual void SetID(const char* id) = 0;
    virtual const char* GetID(void) = 0; // ID in the XML, (EX: <Panel id="ShopCourierControls">)
    virtual void GetPanelType(void) = 0;
    virtual bool HasID() = 0;
    virtual void unk() = 0;
    virtual void unk2() = 0;
    virtual void unk3() = 0;
    virtual void unk4() = 0;
    virtual void unk5() = 0;
    virtual bool LoadLayout(const char* pathToXML, bool, bool) = 0;
    virtual bool LoadLayoutFromString(const char* layoutXML, bool, bool) = 0;
    virtual void LoadLayoutAsync(const char* pathToXML, bool, bool) = 0;
    virtual void LoadLayoutFromStringAsync(const char* layoutXML, bool, bool) = 0;
    virtual bool CreateChildren(const char*) = 0;
    virtual void UnloadLayout(void) = 0;
    virtual bool IsLoaded(void) = 0;
    virtual void SetParent(IUIPanel* parent) = 0;
    virtual IUIPanel* GetParent(void) = 0;
    virtual IUIWindow* GetParentWindow(void) = 0;
    virtual void SetVisible(bool state) = 0;
    virtual bool IsVisible(void) = 0;
    virtual bool IsTransparent(void) = 0;
    virtual void SetLayoutLoadedFromParent(IUIPanel*) = 0;
    virtual void SetPanelIntoContext(IUIPanel*) = 0;
    virtual void* GetLayoutFile(void) = 0;
    virtual void GetLayoutFileLoadedFrom(void) = 0;
    virtual int GetLayoutFileReloadCount(void) = 0;
    virtual void unk6() = 0;
    virtual void unk7() = 0;
    virtual void unk8() = 0;
    virtual IUIPanel* FindChild(const char*) = 0;
    virtual void unk9() = 0;
    virtual void FindChildTraverse(const char*) = 0;
    virtual void unk10() = 0;
    virtual IUIPanel* FindChildInLayoutFile(const char*) = 0;
    virtual void unk11() = 0;
    virtual IUIPanel* FindPanelInLayoutFile(const char*) = 0;
    virtual bool IsDecendantOf(IUIPanel const* const) = 0;
    virtual void RemoveAndDeleteChildren(void) = 0;
    virtual void RemoveAndDeleteChildrenOfType(CPanoramaSymbol) = 0;
    virtual int GetChildCount(void) = 0;
    virtual IUIPanel* GetChild(int) = 0;
    virtual IUIPanel* GetFirstChild(void) = 0;
    virtual IUIPanel* GetLastChild(void) = 0;
    virtual int GetChildIndex(IUIPanel const* const) = 0;
    virtual int GetChildCountOfType(CPanoramaSymbol) = 0;
    virtual int GetHiddenChildCount(void) = 0;
    virtual IUIPanel* GetHiddenChild(int) = 0;
    virtual IUIPanel* FindAncestor(const char*) = 0;
    virtual void sub_131D10() = 0; // new function, added around august 2018
    virtual void SetRepaint(EPanelRepaint) = 0;
    virtual void SetRepaintUpParentChain(void* unk) = 0;
    virtual bool ShouldDrawChildren(IUIPanel*) = 0;
    virtual void EnableBackgroundMovies(bool state) = 0;
    virtual void* AccessIUIStyle() = 0;
    virtual IUIPanelStyle* AccessIUIStyleDirty() = 0;
    virtual void ApplyStyles(bool apply) = 0;
    virtual void AfterStylesApplied(bool, EStyleRepaint, bool, bool) = 0;
    virtual void SetOnStylesChangedNeeded(void) = 0;
    virtual void* AccessChildren(void) = 0;
    virtual void DesiredLayoutSizeTraverse(float, float) = 0;
    virtual void DesiredLayoutSizeTraverse(float*, float*, float, float, bool) = 0;
    virtual void OnContentSizeTraverse(float*, float*, float, float, bool) = 0;
    virtual void LayoutTraverse(float, float, float, float) = 0;
    virtual void OnLayoutTraverse(float, float) = 0;
    virtual void SetPositionFromLayoutTraverse(CUILength, CUILength, CUILength) = 0;
    virtual void InvalidateSizeAndPosition(void) = 0;
    virtual void InvalidatePosition(void) = 0;
    virtual void SetActiveSizeAndPositionTransition(void) = 0;
    virtual void SetActivePositionTransition(void) = 0;
    virtual bool IsSizeValid(void) = 0;
    virtual bool IsPositionValid(void) = 0;
    virtual bool IsChildSizeValid(void) = 0;
    virtual bool IsChildPositionValid(void) = 0;
    virtual bool IsSizeTransitioning(void) = 0;
    virtual bool IsPositionTransitioning(void) = 0;
    virtual bool IsChildPositionTransitioning(void) = 0;
    virtual bool IsChildSizeTransitioning(void) = 0;
    virtual void TransitionPositionApplied(bool) = 0;
    virtual void sub_140EE0();
    virtual void sub_140F00();
    virtual float GetDesiredLayoutWidth(void) = 0; // these might be doubles, need to "double"-check
    virtual float GetDesiredLayoutHeight(void) = 0;
    virtual float GetContentWidth(void) = 0;
    virtual float GetContentHeight(void) = 0;
    virtual float GetActualLayoutWidth(void) = 0;
    virtual float GetActualLayoutHeight(void) = 0;
    virtual float GetActualRenderWidth(void) = 0;
    virtual float GetActualRenderHeight(void) = 0;
    virtual float GetActualXOffset(void) = 0;
    virtual float GetActualYOffset(void) = 0;
    virtual float GetRawActualXOffset(void) = 0;
    virtual float GetRawActualYOffset(void) = 0;
    virtual void unk12() = 0;
    virtual void sub_140FC0() = 0;
    virtual float GetContentsYScrollOffset(void) = 0;
    virtual float GetContentsXScrollOffset(void) = 0;
    virtual void unk_131A10() = 0;
    virtual void unk_152250() = 0;
    virtual void unk_152230() = 0;
    virtual void unk_1522A0() = 0;
    virtual void unk_152270() = 0;
    virtual void unk_1522D0() = 0;
    virtual void unk_1522F0() = 0;
    virtual void unk_152310() = 0;
    virtual void unk_152330() = 0;
    virtual void unk_152350() = 0;
    virtual void unk_152380() = 0;
    virtual void unk_131080() = 0;
    virtual void unk_1310F0() = 0;
    virtual void unk_134E50() = 0;
    virtual void unk_1350C0() = 0;
    virtual void unk_134EF0() = 0;
    virtual void unk_135450() = 0;
    virtual void unk_135470() = 0;
    virtual void unk_131710() = 0;
    virtual void unk_131760() = 0;
    virtual bool CanScrollUp(void) = 0;
    virtual bool CanScrollDown(void) = 0;
    virtual bool CanScrollLeft(void) = 0;
    virtual bool CanScrollRight(void) = 0;
    virtual void AddClass(const char*) = 0;
    virtual void AddClass(CPanoramaSymbol) = 0;
    virtual void AddClasses(CPanoramaSymbol*, unsigned int count) = 0;
    virtual void RemoveClass(const char*) = 0;
    virtual void RemoveClasses(CPanoramaSymbol const* const, unsigned int) = 0;
    virtual void RemoveClasses(const char*) = 0;
    virtual void RemoveAllClasses(void) = 0;
    virtual void sub_137540() = 0;
    virtual void* GetClasses(void) = 0;
    virtual bool HasClass(const char*) = 0;
    virtual bool HasClass(CPanoramaSymbol) = 0;
    virtual bool AscendantHasClass(const char*) = 0;
    virtual bool AscendantHasClass(CPanoramaSymbol) = 0;
    virtual void ToggleClass(const char*) = 0;
    virtual void ToggleClass(CPanoramaSymbol) = 0;
    virtual void SetHasClass(const char*, bool) = 0;
    virtual void SetHasClass(CPanoramaSymbol, bool) = 0;
    virtual void SwitchClass(const char*, const char*) = 0;
    virtual void SwitchClass(const char*, CPanoramaSymbol) = 0;
    virtual void unk_149DF0() = 0;
    virtual void unk_149D50() = 0;
    virtual void unk_149EB0() = 0;
    virtual void unk_149E50() = 0;
    virtual bool AcceptsInput() = 0;
    virtual void SetAcceptsInput(bool state) = 0;
    virtual bool AcceptsFocus() = 0;
    virtual void SetAcceptsFocus(bool state) = 0;
    virtual bool CanAcceptInput() = 0;
    virtual void SetDefaultFocus(const char*) = 0;
    virtual const char* GetDefaultFocus() = 0;
    virtual void SetDisableFocusOnMouseDown(bool state) = 0;
    virtual bool FocusOnMouseDown() = 0;
    virtual void unk_152460() = 0;
    virtual void unk_1523E0() = 0;
    virtual void unk_130E80() = 0;
    virtual void unk_130EB0() = 0;
    virtual void unk_152400() = 0;
    virtual void unk_152420() = 0;
    virtual void unk_152470() = 0;
    virtual void unk_152490() = 0;
    virtual void unk_1318C0() = 0;
    virtual void GetDefaultInputFocus(void) = 0;
    virtual void SetFocus(void) = 0;
    virtual void UpdateFocusInContext(void) = 0;
    virtual void SetFocusDueToHover(void) = 0;
    virtual void SetInputContextFocus(void) = 0;
    virtual unsigned long long GetStyleFlags(void) = 0;
    virtual void AddStyleFlag(EStyleFlags) = 0;
    virtual void RemoveStyleFlag(EStyleFlags) = 0;
    virtual bool IsInspected(void) = 0;
    virtual bool HasHoverStyle(bool) = 0;
    virtual void SetSelected(bool state) = 0;
    virtual bool IsSelected(void) = 0;
    virtual bool HasKeyFocus(void) = 0;
    virtual bool HasDescendantKeyFocus(void) = 0;
    virtual bool IsLayoutLoading(void) = 0;
    virtual void SetEnabled(bool state) = 0;
    virtual bool IsEnabled(void) = 0;
    virtual void unk_146920() = 0;
    virtual void unk_1525B0() = 0;
    virtual void unk13() = 0;
    virtual void sub_125010() = 0;
    virtual void SetAllChildrenActivationEnabled(bool state) = 0;
    virtual void SetHitTestEnabled(bool state) = 0;
    virtual bool HitTestEnabled(void) = 0;
    virtual void SetHitTestEnabledTraverse(bool state) = 0;
    virtual void unk_152630() = 0;
    virtual void unk_152660() = 0;
    virtual void SetDraggable(bool state) = 0;
    virtual bool IsDraggable(void) = 0;
    virtual void SetRememberChildFocus(bool state) = 0;
    virtual bool GetRememberChildFocus(void) = 0;
    virtual void ClearLastChildFocus(void) = 0;
    virtual void SetNeedsIntermediateTexture(bool state) = 0;
    virtual bool GetNeedsIntermediateTexture(void) = 0;
    virtual void unk_152DE0() = 0;
    virtual void unk_152E40() = 0;
    virtual void SetClipAfterTransform(bool state) = 0;
    virtual bool GetClipAfterTransform(void) = 0;
    virtual const char* GetInputNamespace(void) = 0;
    virtual void SetInputNamespace(const char*) = 0;
    virtual void MarkStylesDirty(bool state) = 0;
    virtual bool StylesDirty(void) = 0;
    virtual void sub_12A000() = 0;
    virtual bool ChildStylesDirty() = 0;
    virtual bool ParsePanelEvent(CPanoramaSymbol, const char*) = 0;
    virtual bool IsPanelEventSet(CPanoramaSymbol) = 0;
    virtual bool IsPanelEvent(CPanoramaSymbol) = 0;
    virtual void DispatchPanelEvent(CPanoramaSymbol) = 0;
    virtual void* GetJavaScriptContextParent(void) = 0;
    virtual void* UIImageManager(void) = 0;
    virtual void* UIRenderEngine(void) = 0;
    virtual void* unk_130DF0() = 0; // returns another class like the 2 above
    virtual void PaintTraverse(void) = 0;
    virtual void SetTabIndex(float) = 0;
    virtual float GetTabIndex(void) = 0;
    virtual void SetSelectionPosition(float, float) = 0;
    virtual void SetSelectionPositionX(float) = 0;
    virtual void SetSelectionPositionY(float) = 0;
    virtual float GetSelectionPositionX(void) = 0;
    virtual float GetSelectionPositionY(void) = 0;
    virtual float GetTabIndex_Raw(void) = 0;
    virtual float GetSelectionPositionX_Raw(void) = 0;
    virtual float GetSelectionPositionY_Raw(void) = 0;
    virtual void SetFocusToNextPanel(int, EFocusMoveDirection, bool, float, float, float, float, float) = 0;
    virtual void SetInputFocusToFirstOrLastChildInFocusOrder(EFocusMoveDirection, float, float) = 0;
    virtual void SelectionPosVerticalBoundary(void) = 0;
    virtual void SelectionPosHorizontalBoundary(void) = 0;
    virtual void SetChildFocusOnHover(bool state) = 0;
    virtual bool GetChildFocusOnHover(void) = 0;
    virtual void SetFocusOnHover(bool state) = 0;
    virtual bool GetFocusOnHover(void) = 0;
    virtual void ScrollToTop(void) = 0;
    virtual void ScrollToBottom(void) = 0;
    virtual void ScrollToLeftEdge(void) = 0;
    virtual void ScrollToRightEdge(void) = 0;
    virtual void ScrollParentToMakePanelFit(ScrollBehavior_t, bool) = 0;
    virtual void ScrollToFitRegion(float, float, float, float, ScrollBehavior_t, bool, bool) = 0;
    virtual bool CanSeeInParentScroll(void) = 0;
    virtual void OnScrollPositionChanged(void) = 0;
    virtual void SetSendChildScrolledIntoViewEvents(bool) = 0;
    virtual void OnCheckChildrenScrolledIntoView(void) = 0;
    virtual void FireScrolledIntoViewEvent(void) = 0;
    virtual void FireScrolledOutOfViewEvent(void) = 0;
    virtual bool IsScrolledIntoView(void) = 0;
    virtual void SortChildren() = 0; // (int (*)(IUIPanelClient * const*,IUIPanelClient * const*))
    virtual void AddChild(IUIPanel*) = 0;
    virtual void AddChildSorted() = 0; // (bool (*)(IUIPanelClient * const&,IUIPanelClient * const&),IUIPanel *)
    virtual void ResortChild() = 0; // (bool (*)(IUIPanelClient * const&,IUIPanelClient * const&),IUIPanel *)
    virtual void RemoveChild(IUIPanel*) = 0;
    virtual void unk_139310() = 0;
    virtual void unk_1393C0() = 0;
    virtual void unk_131260() = 0;
    virtual void unk_131270() = 0;
    virtual void SetMouseCanActivate(EMouseCanActivate, const char*) = 0;
    virtual EMouseCanActivate GetMouseCanActivate(void) = 0;
    virtual IUIPanel* FindParentForMouseCanActivate(void) = 0;
    virtual bool ReloadLayout(CPanoramaSymbol) = 0;
    virtual void ReloadStyleFileTraverse(CPanoramaSymbol) = 0;
    virtual bool HasOnActivateEvent(void) = 0;
    virtual bool HasOnMouseActivateEvent(void) = 0;
    virtual void SetupJavascriptObjectTemplate(void) = 0;
    virtual void SetLayoutFile(CPanoramaSymbol) = 0;
    virtual void BuildMatchingStyleList() = 0; // (CUtlVector<CascadeStyleFileInfo_t,CUtlMemory<CascadeStyleFileInfo_t,int>> *)
    virtual void GetAttribute(const char*, int) = 0;
    virtual void GetAttribute(const char*, const char*) = 0;
    virtual void unk_132680() = 0;
    virtual void GetAttribute(const char*, unsigned int) = 0;
    virtual void GetAttribute(const char*, unsigned long long) = 0;
    virtual void SetAttribute(const char*, int) = 0;
    virtual void SetAttribute(const char*, const char*) = 0;
    virtual void SetAttribute(const char*, unsigned int) = 0;
    virtual void SetAttribute(const char*, unsigned long long) = 0;
    virtual void SetAttribute() = 0;
    virtual void unk_132770() = 0;
    virtual void unk_132830() = 0;
    virtual void unk_132810() = 0;
    virtual void unk_1327C0() = 0;
    virtual void unk_132880() = 0;
    virtual void unk_13D2D0() = 0;
    virtual void unk_13D110() = 0;
    virtual void unk_13D350() = 0;
    virtual void unk_13D3D0() = 0;
    virtual void unk_13D450() = 0;
    virtual void unk_13D950() = 0;
    virtual void unk_13D870() = 0;
    virtual void unk_13D690() = 0;
    virtual void unk_13D420() = 0;
    virtual void SetAnimation(const char*, float, float, EAnimationTimingFunction, EAnimationDirection, float) = 0;
    virtual void UpdateVisibility(bool) = 0;
    virtual void unk14() = 0;
    virtual void SetProperty(CPanoramaSymbol, const char*) = 0;
    virtual void FindChildrenWithClass() = 0; // (char const*,CUtlVector<IUIPanel *,CUtlMemory<IUIPanel *,int>> &)
    virtual void FindChildrenWithClassTraverse() = 0; // (char const*,CUtlVector<IUIPanel *,CUtlMemory<IUIPanel *,int>> &)
    virtual void PlayFocusChangeSound(int, float) = 0;
    virtual void unk15() = 0;
    virtual void ClearPanelEvents(CPanoramaSymbol) = 0;
    virtual void SetPanelEvent(CPanoramaSymbol, IUIEvent*) = 0;
    virtual void SetPanelEvent2() = 0; // (CPanoramaSymbol,CUtlVector<IUIEvent *,CUtlMemory<IUIEvent *,int>> *)
    virtual bool GetAnalogStickScrollingEnabled(void) = 0;
    virtual void EnableAnalogStickScrolling(bool state) = 0;
    virtual void SetMouseTracking(bool state) = 0;
    virtual void SetInScrollbarConstruction(bool state) = 0;
    virtual void* GetVerticalScrollBar(void) = 0;
    virtual void* GetHorizontalScrollBar(void) = 0;
    virtual void GetPanelEvents(CPanoramaSymbol) = 0;
    virtual bool HasBeenLayedOut(void) = 0;
    virtual void OnStyleTransitionsCleanup(void) = 0;
    virtual void unk_1529D0() = 0;
    virtual void unk_1529F0() = 0;
    virtual void unk_152A00() = 0;
    virtual void unk_152A20() = 0;
    virtual void unk_136B20() = 0;
    virtual void unk_152A30() = 0;
    virtual void unk_139260() = 0;
    virtual void unk_1331A0() = 0;
    virtual void unk_1529A0() = 0;
    virtual void unk_1529B0() = 0;
    virtual void unk_1529C0() = 0;
};

class IUIEvent
{
public:
    /*
    virtual void DESTROY() = 0;
    virtual void DESTROY2() = 0;
    virtual IUIPanel* GetTargetPanel(void);
    virtual void SetTargetPanel(IUIPanel const *);
    virtual CPanoramaSymbol* GetEventType(void);
    virtual bool CanBubble(void);
    virtual void Dispatch(CUtlAbstractDelegate);
    virtual void Copy(void);
    virtual void GetJavaScriptArgs(int *,v8::Handle<v8::Value> value);
    */
    IUIPanel* pos1; //0x0000
    char pad_0008[8]; //0x0008
    IUIPanel* pos2; //0x0010
    IUIPanel* pos3; //0x0018
    char pad_0020[24]; //0x0020
    IUIPanel* pos4; //0x0038
    char pad_0040[8]; //0x0040
    IUIPanel* pos5; //0x0048
    IUIPanel* pos6; //0x0050
    char pad_0058[8]; //0x0058
    IUIPanel* pos7; //0x0060
    IUIPanel* pos8; //0x0068
    char pad_0070[16]; //0x0070
    IUIPanel* pos9; //0x0080
    IUIPanel* pos10; //0x0088
    IUIPanel* pos11; //0x0090
    char pad_0098[24]; //0x0098
    IUIPanel* pos12; //0x00B0
    IUIPanel* pos13; //0x00B8
    char pad_00C0[8]; //0x00C0
    IUIPanel* pos14; //0x00C8
    char pad_00D0[16]; //0x00D0
    IUIPanel* pos15; //0x00E0
    char pad_00E8[8]; //0x00E8
    char* eventName; //0x00F0
    char pad_00F8[16]; //0x00F8
    IUIPanel* pos16; //0x0108
    char pad_0110[8]; //0x0110
    IUIPanel* pos17; //0x0118
    char pad_0120[40]; //0x0120
    IUIPanel* pos18; //0x0148
    char pad_0150[8]; //0x0150
    IUIPanel* pos19; //0x0158
    char pad_0160[8]; //0x0160
    IUIPanel* pos20; //0x0168
    char pad_0170[32]; //0x0170
    IUIPanel* pos21; //0x0190
    char pad_0198[360]; //0x0198
};


class UIEngine
{
public:
    virtual void DESTROY() = 0; // 0
    virtual void DESTROY2() = 0;
    virtual void StartupSubsystems(IUISettings*, void* PlatWindow_t__) = 0;
    virtual void ConCommandInit(void* IConCommandBaseAccessor) = 0;
    virtual void Shutdown(void) = 0;
    virtual void RequestShutdown(void) = 0;
    virtual void Run(void) = 0;
    virtual void RunFrame(void) = 0;
    virtual void SetAggressiveFrameRateLimit(bool) = 0;
    virtual bool IsRunning(void) = 0;
    virtual bool HasFocus(void) = 0;
    virtual double GetCurrentFrameTime(void) = 0;
    virtual void unk0() = 0; // getter
    virtual void unk1() = 0; // setter ^^
    virtual void INT3_WRAPPER() = 0;
    virtual void INT3_WRAPPER2() = 0;
    virtual void INT3_WRAPPER3() = 0;// probably windows specific
    virtual void INT3_WRAPPER4() = 0;
    virtual void INT3_WRAPPER5() = 0;
    virtual void CreateTextLayout(char const*, char const*, float, float, EFontWeight, EFontStyle, ETextAlign, bool, bool, int, float, float) = 0;
    virtual void CreateTextLayout(wchar_t const*, char const*, float, float, EFontWeight, EFontStyle, ETextAlign, bool, bool, int, float, float) = 0;
    virtual void FreeTextLayout(IUITextLayout*) = 0;
    virtual void GetSomeFontThing(void) = 0; //similar to function below
    virtual void GetSortedValidFontNames(void) = 0;
    virtual IUIInputEngine* UIInputEngine(void) = 0;
    virtual IUILocalize* UILocalize(void) = 0;
    virtual IUISoundSystem* UISoundSystem(void) = 0;
    virtual IUISettings* UISettings(void) = 0;
    virtual IUILayoutManager* UILayoutManager(void) = 0;
    virtual IUIFileSystem* UIFileSystem(void) = 0;
    virtual void INT3_WRAPPER6() = 0;
    virtual void RegisterFrameFunc(void (*)(void)) = 0;
    virtual void ReloadLayoutFile(CPanoramaSymbol) = 0;
    virtual void ToggleDebugMode(void) = 0;
    virtual const char* GetConsoleHistory(void) = 0;
    virtual PanelWrapper* CreatePanel(void) = 0;
    virtual void PanelDestroyed(IUIPanel*, IUIPanel*) = 0;
    virtual bool IsValidPanelPointer(IUIPanel const*) = 0;
    virtual PanelHandle_t* GetPanelHandle(IUIPanel const*) = 0;
    virtual IUIPanel* GetPanelPtr(PanelHandle_t const&) = 0;
    virtual void CallBeforeStyleAndLayout(IUIPanel*) = 0;
    virtual void RegisterForPanelDestroyed();//CUtlDelegate<void ()(IUIPanel const*,IUIPanel*)>) = 0;
    virtual void UnregisterForPanelDestroyed();//CUtlDelegate<void ()(IUIPanel const*,IUIPanel*)>) = 0;
    virtual void RegisterEventHandler(CPanoramaSymbol, IUIPanel*/*, CUtlAbstractDelegate*/) = 0;
    virtual void UnregisterEventHandler(CPanoramaSymbol, IUIPanel*/*, CUtlAbstractDelegate*/) = 0;
    virtual void RegisterEventHandler(CPanoramaSymbol, IUIPanelClient*/*, CUtlAbstractDelegate*/) = 0;
    virtual void UnregisterEventHandler(CPanoramaSymbol, IUIPanelClient*/*, CUtlAbstractDelegate*/) = 0;
    virtual void UnregisterEventHandlersForPanel(IUIPanel*) = 0;
    virtual void RegisterForUnhandledEvent(CPanoramaSymbol/*, CUtlAbstractDelegate*/) = 0;
    virtual void UnregisterForUnhandledEvent(CPanoramaSymbol/*, CUtlAbstractDelegate*/) = 0;
    virtual void UnregisterForUnhandledEvents(void*) = 0;
    virtual bool HaveEventHandlersRegisteredForType(CPanoramaSymbol) = 0;
    virtual void RegisterPanelTypeEventHandler(CPanoramaSymbol, CPanoramaSymbol/*, CUtlAbstractDelegate*/, bool) = 0;
    virtual void DispatchEvent(IUIEvent*) = 0;
    virtual void DispatchEventAsync(float, IUIEvent*) = 0;
    virtual bool AnyHandlerRegisteredForEvent(CPanoramaSymbol const&) = 0;
    virtual CPanoramaSymbol* GetLastDispatchedEventSymbol(void) = 0;
    virtual IUIPanel* GetLastDispatchedEventTargetPanel(void) = 0; // This function can fail sometimes and you need to check the result/call it later (YUCK!)
    virtual void RegisterEventFilter(/*, CUtlAbstractDelegate*/) = 0;
    virtual void UnregisterEventFilter(/*, CUtlAbstractDelegate*/) = 0;
    virtual void LayoutAndPaintWindows(void) = 0;
    virtual const char* GetApplicationInstallPath(void) = 0;
    virtual const char* GetApplicationUserDataPath(void) = 0;
    virtual void RegisterNamedLocalPath(char const*, char const*, bool, bool) = 0;
    virtual void RegisterNamedUserPath(char const*, char const*, bool, bool) = 0;
    virtual void RegisterCustomFontPath(char const*) = 0;
    virtual void GetLocalPathForNamedPath(char const*) = 0;
    virtual void GetLocalPathForRelativePath(char const*, char const*, void* CUtlString) = 0;
    virtual void RegisterNamedRemoteHost(char const*, char const*) = 0;
    virtual void GetRemoteHostForNamedHost(char const*) = 0;
    virtual void RegisterXHeader(char const*, char const*) = 0;
    virtual int GetXHeaderCount(void) = 0;
    virtual void GetXHeader(int, void* CUtlString, void* CUtlString2) = 0;
    virtual void SetCookieHeaderForNamedRemoteHost();//char const*,CUtlVector<CUtlString,CUtlMemory<CUtlString,int>> const&) = 0;
    virtual void SetCookieHeaderForRemoteHost();//char const*,CUtlVector<CUtlString,CUtlMemory<CUtlString,int>> const&) = 0;
    virtual void GetCookieHeadersForNamedRemoteHost(char const*) = 0;
    virtual void GetCookieHeadersForRemoteHost(char const*) = 0;
    virtual void GetCookieValueForRemoteHost(char const*, char const*, void* CUtlString) = 0;
    virtual void BSetCookieForWebRequests(char const*, char const*, char const*) = 0;
    virtual void BClearCookieForWebRequests(char const*, char const*, char const*) = 0;
    virtual void* AccessHTMLController(void) = 0;
    virtual void unk() = 0; // _SDL_ShowSimpleMessageBox with yes/no
    virtual void AddFrameListener(IUIEngineFrameListener*) = 0;
    virtual void RemoveFrameListener(IUIEngineFrameListener*) = 0;
    virtual void RegisterMouseCanActivateParent(IUIPanel*, char const*) = 0;
    virtual void UnregisterMouseCanActivateParent(IUIPanel*) = 0;
    virtual void GetMouseCanActivateParent(IUIPanel*) = 0;
    virtual bool AnyWindowHasFocus(void) = 0;
    virtual bool AnyVisibleWindowHasFocus(void) = 0;
    virtual bool AnyOverlayWindowHasFocus(void) = 0;
    virtual IUIWindow* GetFocusedWindow(void) = 0;
    virtual float GetLastInputTime(void) = 0;
    virtual float UpdateLastInputTime(void) = 0;
    virtual void ClearClipboard(void) = 0;
    virtual void CopyToClipboard(char const*, char const*) = 0;
    virtual void GetClipboardText(void* CUtlString, void* CUtlString2) = 0;
    virtual const char* GetDisplayLanguage(void) = 0;
    virtual void unk2() = 0;
    virtual void unk3() = 0;
    virtual void unk4() = 0;
    virtual bool HasOverlayForApp(unsigned long long, unsigned long long) = 0;
    virtual void TrackOverlayForApp(unsigned long long, unsigned long long, void*) = 0;
    virtual void DeleteOverlayInstanceForApp(unsigned long long, unsigned long long, void*) = 0;
    virtual void OverlayForApp(unsigned long long, unsigned long long) = 0;
    virtual void unk5() = 0;
    virtual IUIPanelStyle* AllocPanelStyle(IUIPanel*, float) = 0;
    virtual void FreePanelStyle(IUIPanelStyle*) = 0;
    virtual void SetPanelWaitingAsyncDelete(IUIPanel*) = 0;
    virtual bool IsPanelWaitingAsyncDelete(IUIPanel*) = 0;
    virtual void PulseActiveControllerHaptic();//IUIEngine::EHapticFeedbackPosition,IUIEngine::EHapticFeedbackStrength) = 0;
    virtual void SomethingControllerHapticRelated() = 0;
    virtual void MarkLayerToRepaintThreadSafe(unsigned long long) = 0;
    virtual void AddDirectoryChangeWatch(char const*) = 0;
    virtual int GetWheelScrollLines(void) = 0; // default 3
    virtual int RunScript(IUIPanel* panel, char const* entireJSCode, char const* pathToXMLContext, int, int, bool alreadyCompiled) = 0;
    virtual void ExposeObjectTypeToJavaScript(char const*, void*/*, , CUtlAbstractDelegate&*/) = 0;
    virtual bool IsObjectTypeExposedToJavaScript(char const*) = 0;
    virtual void ExposeGlobalObjectToJavaScript(char const*, void*, char const*, bool) = 0;
    virtual void ClearGlobalObjectForJavaScript(char const*, void*) = 0;
    virtual void DeleteJSObjectInstance(IUIJSObject*) = 0;
    virtual IUIPanel* GetPanelForJavaScriptContext();//v8::Context *) = 0;
    virtual void* GetJavaScriptContextForPanel(IUIPanel*) = 0;
    virtual void OutputJSExceptionToConsole();//v8::TryCatch &,IUIPanel *) = 0;
    virtual void AddGlobalV8FunctionTemplate();//char const*,v8::Handle<v8::FunctionTemplate> *,bool) = 0;
    virtual void* GetV8GlobalContext(void) = 0;
    virtual void GetCurrentV8ObjectTemplateToSetup(void) = 0; //gets offset.
    virtual void GetCurrentV8ObjectTemplateToSetup2(void) = 0; //gets offset and calls some function.
    virtual void Grabber3(void) = 0; // returns offset in class
    virtual void Grabber4(void) = 0; // returns offset in class.
    virtual void UIStyleFactory(void) = 0;
    virtual void GetV8Isolate(void) = 0;
    virtual void RunFunction() = 0;
    virtual void RunFunction2() = 0; //different args
    virtual void CreateV8PanelInstance(IUIPanel*) = 0;
    virtual void CreateV8PanelStyleInstance(IUIPanelStyle*) = 0;
    virtual void CreateV8ObjectInstance(char const*, void*, IUIJSObject*) = 0;
    virtual void _unk() = 0;
    virtual void InitiateAsyncJSONWebAPIRequest();//EHTTPMethod,CUtlString,IUIPanel *,void *,CJSONWebAPIParams *,uint) = 0;
    virtual void InitiateAsyncJSONWebAPIRequest(int overloadMeme);//EHTTPMethod,CUtlString,CUtlDelegate<void ()(unsigned long long,KeyValues *,void *)>,void *,CJSONWebAPIParams *,uint) = 0;
    virtual void CancelAsyncJSONWebAPIRequest(unsigned int) = 0;
    virtual void ResolvePath(char const*) = 0;
    virtual void RegisterEventWithEngine(CPanoramaSymbol, UIEventFactory) = 0;
    virtual bool IsValidEventName(CPanoramaSymbol) = 0;
    virtual bool IsValidPanelEvent(CPanoramaSymbol, int*) = 0;
    virtual void CreateInputEventFromSymbol(CPanoramaSymbol, IUIPanel*, EPanelEventSource_t, int) = 0;
    virtual void CreateEventFromString(IUIPanel*, char const*, char const**) = 0;
    virtual void unk11();
    virtual void RegisterPanelFactoryWithEngine(CPanoramaSymbol, CPanel2DFactory*) = 0;
    virtual bool RegisteredPanelType(CPanoramaSymbol) = 0;
    virtual PanelWrapper* CreatePanel(CPanoramaSymbol* panelType, char const* id, IUIPanel* createInThisParent) = 0; // paneltype (ex: Panel, Label), id (ex: <Label id="swag">)
    virtual void CreateDebuggerWindow(void) = 0;
    virtual void CloseDebuggerWindow(void) = 0;
    virtual void RegisterScheduledDelegate();// double,CUtlDelegate<void ()(void)> ) = 0;
    virtual void CancelScheduledDelegate(int) = 0;
    virtual float GetLastScheduledDelegateRunTime(void) = 0;
    virtual CPanoramaSymbol MakeSymbol(char const*) = 0; // if the symbol already exists, you'll get that one.
    virtual const char* ResolveSymbol(unsigned short) = 0; // if you pass an invalid number into here, it can crash the program.
    virtual void QueueDecrementRefNextFrame();//CRefCounted<CRefCountServiceBase<true,CRefMT>> *) = 0;
    virtual void RegisterJSGenericCallback();//IUIPanel *,v8::Handle<v8::Function>) = 0;
    virtual void InvokeJSGenericCallback();//int,int,v8::Handle<v8::Value> *,v8::Handle<v8::Value> *) = 0;
    virtual void UnregisterJSGenericCallback(int) = 0;
    virtual int GetNumRegisterJSScopes(void) = 0;
    virtual void GetRegisterJSScopeInfo(int, RegisterJSScopeInfo_t*) = 0;
    virtual void GetRegisterJSEntryInfo(int, int, RegisterJSEntryInfo_t*) = 0;
    virtual void StartRegisterJSScope(char const*, char const*) = 0;
    virtual void EndRegisterJSScope(void) = 0;
    virtual void NewRegisterJSEntry(char const*, unsigned int, char const*, RegisterJSType_t) = 0;
    virtual void SetRegisterJSEntryParams(int, unsigned char, RegisterJSType_t*) = 0;
    virtual void _padding() = 0;
    virtual void ClearFileCache(void) = 0;
    virtual void PrintCacheStatus(void) = 0;
    virtual void GetWindowsForDebugger();//CUtlVector<IUIWindow *,CUtlMemory<IUIWindow *,int>> &) = 0;
    virtual void SetPaintCountTrackingEnabled(bool) = 0;
    virtual bool GetPaintCountTrackingEnabled(void) = 0;
    virtual void IncrementPaintCountForPanel(unsigned long long, bool, double) = 0;
    virtual void GetPanelPaintInfo(unsigned long long, unsigned int&, bool&, double&) = 0;
    virtual bool HasAnyWindows(void) = 0;
    virtual void TextEntryFocusChange(IUIPanel*) = 0;
    virtual void TextEntryInvalid(IUIPanel*) = 0;
    virtual void SetClipboardText(const char* text) = 0; // wrapper for _SDL_SetClipboardText
    virtual const char* GetClipboardText() = 0; // wrapper for _SDL_GetClipboardText
    virtual void OnFileCacheRemoved(CPanoramaSymbol) = 0;
    virtual void RunPlatformFrame(void) = 0;
    virtual void CreateSoundSystem(void) = 0;
};